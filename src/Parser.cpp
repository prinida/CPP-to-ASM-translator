#include "Parser.h"

#include <algorithm>
#include <iostream>
#include <stack>

Parser::Parser(DynamicTable<Token>& _tokenTable, std::map<unsigned int, ParseTableElement>& _parseTable, std::string _errorsFile, std::string _prioritiesFile, std::string _postfixFile) :
    parseTable(_parseTable),
    tokenTable(_tokenTable)
{
    errors.open(_errorsFile, std::ios::app);

    if (!errors.is_open())
        std::cout << "Unable to open error file" << std::endl;

    postfixFile.open(_postfixFile);

    if (!postfixFile.is_open())
        std::cout << "Unable to open postfix file" << std::endl;

    std::ifstream prFile;
    prFile.open(_prioritiesFile);

    if (!prFile.is_open())
        std::cout << "Unable to open priorities file" << std::endl;
    else
    {
        std::string str;
        int priority;

        while (prFile >> str >> priority)
            priorities[str] = priority;
    }
}

void Parser::doParse()
{
    int id = 1;

    std::stack<unsigned int> stack;
    stack.push(0);

    bool nextSym = true;
    Token token = tokenTable.pop();
    Token prevToken = token;

    ParseTableElement element;

    int count = 0;

    while (!tokenTable.isTableEmpty() && id != 0)
    {
        element = parseTable[id];

        std::vector<std::string> terms = element.getTerminals();

        if (terms.size() == 1)
            for (int k = 0; k < terms.size(); k++)
            {
                if ((terms[k] == token.getTokenValue() || terms[k] == token.getTokenStringName(token.getTokenName())))
                {
                    infix.push_back(terms[k]);
                    infixValue.push_back(token.getTokenValue());
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
            if (prevToken.getIsTokenLastInLine())
                lineNum = prevToken.getTokenLine();
            else
                lineNum = token.getTokenLine();

            printErrorMessageInFile("Parser has detected an error in line[" + std::to_string(lineNum) + "]", element.getTerminals());
            success = false;

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
            token = tokenTable.pop();

            if (token.getTokenValue() == prevToken.getTokenValue())
            {
                infix.push_back("&&&");
                infixValue.push_back("&&&");
            }
        }
    }

    infix.erase(std::unique(infix.begin(), infix.end()), infix.end());
    infixValue.erase(std::unique(infixValue.begin(), infixValue.end()), infixValue.end());

    auto iterInfix = std::find(infix.begin(), infix.end(), "&&&");
    auto iterInfixValue = std::find(infixValue.begin(), infixValue.end(), "&&&");

    while (iterInfix != infix.end())
    {
        infix.erase(iterInfix);
        infixValue.erase(iterInfixValue);

        iterInfix = std::find(infix.begin(), infix.end(), "&&&");
        iterInfixValue = std::find(infixValue.begin(), infixValue.end(), "&&&");
    }

    if (success)
        makePostfix();

    errors.close();
    postfixFile.close();
}

void Parser::makePostfix()
{
    std::stack<std::string> labelStack;
    int labelNum = 1;
    std::stack<std::string> stack;
    std::string curr;

    for (int k = 4; k < infix.size(); k++)
    {
        curr = infix[k];

        if (curr == "CONSTANT" || curr == "IDENTIFIER" || curr == "NEW_IDENTIFIER")
            postfix.push_back(infixValue[k]);

        else if (priorities.find(curr) != priorities.end())
        {
            while (stack.size() != 0 && priorities[curr] >= priorities[stack.top()] && stack.top() != "(")
            {
                postfix.push_back(stack.top());
                stack.pop();
            }

            stack.push(curr);

            if (stack.top() == "else")
            {
                postfix.push_back(stack.top());
                stack.pop();

                std::string lastLabel = labelStack.top();
                labelStack.pop();

                postfix.push_back(labelStack.top() + ":");
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
                postfix.push_back(stack.top());

                if (stack.top() == "==" || stack.top() == "!=" || stack.top() == "<")
                {
                    labels.push_back("m" + std::to_string(labelNum));
                    postfix.push_back("m" + std::to_string(labelNum));
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
                    postfix.push_back(stack.top());
                    stack.pop();
                }
            }
        }
        else if (curr == "}")
        {
            if (k < infix.size() - 1 && infix[k + 1] == "else")
            {
                labels.push_back("m" + std::to_string(labelNum));
                postfix.push_back("m" + std::to_string(labelNum));
                labelStack.push("m" + std::to_string(labelNum));
                labelNum++;
            }
            else if (labelStack.size() != 0)
            {
                postfix.push_back(labelStack.top() + ":");
                labelStack.pop();
            }
        }
        else if (curr == ";")
        {
            while (stack.size() != 0)
            {
                postfix.push_back(stack.top());
                stack.pop();
            }
        }
    }

    while (stack.size() != 0)
    {
        postfix.push_back(stack.top());
        stack.pop();
    }

    postfix.push_back("[int main()]");

    for (int i = 0; i < postfix.size(); i++)
        postfixFile << postfix[i] << " ";
    postfixFile << "\n";
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

    errors << errorMsg;
}
