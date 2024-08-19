#include "DynamicTable.h"
#include "Parser.h"
#include "ParseTableElement.h"
#include "Token.h"

#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iosfwd>
#include <iostream>
#include <map>
#include <stack>
#include <string>
#include <vector>

Parser::Parser(
    DynamicTable<Token>& tokenTable,
    std::map<unsigned int, ParseTableElement>& parseTable,
    std::string errorsFile,
    std::string prioritiesFile,
    std::string postfixFile) :
    m_parseTable(parseTable),
    m_tokenTable(tokenTable)
{
    m_errors.open(errorsFile, std::ios::app);
    m_postfixFile.open(postfixFile);

    std::ifstream prFile;
    prFile.open(prioritiesFile);

    if (!prFile.is_open())
    {
        size_t num = prioritiesFile.find_last_of("\\");
        std::string name = prioritiesFile.substr(num + 1, prioritiesFile.size() - num);

        std::cout << "Failed to open file " << name << std::endl;
        system("pause");
        exit(0);
    }

    std::string str;
    int priority;

    while (prFile >> str >> priority)
        m_priorities[str] = priority;
}

void Parser::doParse()
{
    int id = 1;

    std::stack<unsigned int> stack;
    stack.push(0);

    bool nextSym = true;
    Token token = m_tokenTable.pop();
    Token prevToken = token;

    ParseTableElement element;

    int count = 0;

    while (!m_tokenTable.isTableEmpty() && id != 0)
    {
        element = m_parseTable[id];

        std::vector<std::string> terms = element.getTerminals();

        if (terms.size() == 1)
            for (int k = 0; k < terms.size(); k++)
            {
                if ((terms[k] == token.getValue() || terms[k] == token.getStringName(token.getName())))
                {
                    m_infix.push_back(terms[k]);
                    m_infixValue.push_back(token.getValue());
                }
            }

        if (element.isTerminalsContain(token))
        {
            nextSym = element.getAccept();

            if (element.getJump() == 0)
            {
                id = stack.top();
                stack.pop();
            }
            else
            {
                if (element.getStack())
                    stack.push(id + 1);

                id = element.getJump();
            }
        }
        else if (element.getError())
        {
            unsigned int lineNum;
            if (prevToken.getIsLastInLine())
                lineNum = prevToken.getLine();
            else
                lineNum = token.getLine();

            errorHandling("Parser has detected an error in line[" + std::to_string(lineNum) + "]", element.getTerminals());

            break;
        }
        else
        {
            id++;
            nextSym = false;
        }

        if (nextSym)
        {
            prevToken = token;
            token = m_tokenTable.pop();

            if (token.getValue() == prevToken.getValue())
            {
                m_infix.push_back("&&&");
                m_infixValue.push_back("&&&");
            }
        }
    }

    m_infix.erase(std::unique(m_infix.begin(), m_infix.end()), m_infix.end());
    m_infixValue.erase(std::unique(m_infixValue.begin(), m_infixValue.end()), m_infixValue.end());

    auto iterInfix = std::find(m_infix.begin(), m_infix.end(), "&&&");
    auto iterInfixValue = std::find(m_infixValue.begin(), m_infixValue.end(), "&&&");

    while (iterInfix != m_infix.end())
    {
        m_infix.erase(iterInfix);
        m_infixValue.erase(iterInfixValue);

        iterInfix = std::find(m_infix.begin(), m_infix.end(), "&&&");
        iterInfixValue = std::find(m_infixValue.begin(), m_infixValue.end(), "&&&");
    }

    if (m_success)
        makePostfix();

    m_errors.close();
    m_postfixFile.close();
}

void Parser::makePostfix()
{
    std::stack<std::string> labelStack;
    int labelNum = 1;
    std::stack<std::string> stack;
    std::string curr;

    for (int k = 4; k < m_infix.size(); k++)
    {
        curr = m_infix[k];

        if (curr == "CONSTANT" || curr == "IDENTIFIER" || curr == "NEW_IDENTIFIER")
            m_postfix.push_back(m_infixValue[k]);

        else if (m_priorities.find(curr) != m_priorities.end())
        {
            while (stack.size() != 0 && m_priorities[curr] >= m_priorities[stack.top()] && stack.top() != "(")
            {
                m_postfix.push_back(stack.top());
                stack.pop();
            }

            stack.push(curr);

            if (stack.top() == "else")
            {
                m_postfix.push_back(stack.top());
                stack.pop();

                std::string lastLabel = labelStack.top();
                labelStack.pop();

                m_postfix.push_back(labelStack.top() + ":");
                labelStack.pop();

                labelStack.push(lastLabel);
            }
        }
        else if (curr == "(")
            stack.push(curr);
        else if (curr == ")")
        {
            while (stack.top() != "(")
            {
                m_postfix.push_back(stack.top());

                if (stack.top() == "==" || stack.top() == "!=" || stack.top() == "<")
                {
                    m_labels.push_back("m" + std::to_string(labelNum));
                    m_postfix.push_back("m" + std::to_string(labelNum));
                    labelStack.push("m" + std::to_string(labelNum));
                    labelNum++;
                }

                stack.pop();
            }

            if (stack.top() == "(")
            {
                stack.pop();

                if (stack.top() == "if")
                {
                    m_postfix.push_back(stack.top());
                    stack.pop();
                }
            }
        }
        else if (curr == "}")
        {
            if (k < m_infix.size() - 1 && m_infix[k + 1] == "else")
            {
                m_labels.push_back("m" + std::to_string(labelNum));
                m_postfix.push_back("m" + std::to_string(labelNum));
                labelStack.push("m" + std::to_string(labelNum));
                labelNum++;
            }
            else if (labelStack.size() != 0)
            {
                m_postfix.push_back(labelStack.top() + ":");
                labelStack.pop();
            }
        }
        else if (curr == ";")
        {
            while (stack.size() != 0)
            {
                m_postfix.push_back(stack.top());
                stack.pop();
            }
        }
    }

    while (stack.size() != 0)
    {
        m_postfix.push_back(stack.top());
        stack.pop();
    }

    m_postfix.push_back("[int main()]");

    for (int i = 0; i < m_postfix.size(); i++)
        m_postfixFile << m_postfix[i] << " ";
    m_postfixFile << "\n";
}

void Parser::errorHandling(std::string errorText, std::vector<std::string> possibleFixes)
{
    m_success = false;
    printErrorMessageInFile(errorText, possibleFixes);
}

void Parser::printErrorMessageInFile(std::string errorText, std::vector<std::string> possibleFixes)
{
    std::string errorMsg;

    errorMsg += "--------------------------------\n";
    errorMsg += "Error type: syntax error.\n";
    errorMsg += "Error text: " + errorText + ".\n";
    errorMsg += "Possible corrections: \n";

    for (int i = 1; i <= possibleFixes.size(); i++)
    {
        errorMsg += std::to_string(i) + ". " + possibleFixes[i - 1] + "\n";
    }

    errorMsg += "--------------------------------";
    errorMsg += "\n";

    m_errors << errorMsg;
}
