#include "DynamicTable.h"
#include "Enums.h"
#include "Identifier.h"
#include "LexicalAnalyzer.h"
#include "Literal.h"
#include "StaticTable.h"
#include "Token.h"

#include <cstdlib>
#include <iosfwd>
#include <iostream>
#include <stack>
#include <string>
#include <utility>

LexicalAnalyzer::LexicalAnalyzer(
    StaticTable<char>& alphabet, 
    StaticTable<std::string>& keyWords, 
    StaticTable<std::string>& operators, 
    StaticTable<std::string>& separators, 
    DynamicTable<Identifier>& identifiers, 
    DynamicTable<Literal>& literals, 
    DynamicTable<Token>& tokenTable, 
    std::string programFile, 
    std::string errorsFile) :
    m_alphabet(alphabet),
    m_keyWords(keyWords),
    m_operators(operators),
    m_separators(separators),
    m_identifiers(identifiers),
    m_literals(literals),
    m_tokenTable(tokenTable)
{
    m_sourceFile.open(programFile, std::ios::binary);

    // checking the source program file is opened
    if (!m_sourceFile.is_open())
    {
        size_t num = programFile.find_last_of("\\");
        std::string name = programFile.substr(num + 1, programFile.size() - num);

        std::cout << "Failed to open file " << name << std::endl;
        system("pause");
        exit(0);
    }

    m_errors.open(errorsFile);
}

void LexicalAnalyzer::doLexicalAnalysis()
{
    char c;
    m_sourceFile.get(c);
    states CS = IS_START;
    Token token;
    int currentLineNumber = 1; // number of line in the source program file

    std::stack<std::string> specifierStack; // stack for type's specifiers for identifiers

    // finite state machine that goes from the beginning to the end of the source file
    while (!m_sourceFile.eof())
    {
        switch (CS)
        {
            case IS_START:
            {
                while ((c == ' ') || (c == '\t') || (c == '\n') || (c == '\r'))
                {
                    if (c == '\n')
                        currentLineNumber++;

                    m_sourceFile.get(c);
                }

                if (m_alphabet.contains(c))
                {
                    if (((c >= 'A') && (c <= 'Z')) || ((c >= 'a') && (c <= 'z')) || (c == '_'))
                        CS = IS_IDENTIFIER;
                    else if ((c >= '0') && (c <= '9'))
                        CS = IS_NUMBER;
                    else
                        CS = IS_SEPARATOR;
                }
                else if (c == '/')
                {
                    m_sourceFile.get(c);
                    if (c == '*')
                    {
                        std::string str;
                        m_sourceFile.get(c);
                        str += c;
                        m_sourceFile.get(c);
                        str += c;

                        while (str != "*/")
                        {
                            m_sourceFile.get(c);
                            std::swap(str[0], str[1]);
                            str[1] = c;

                            if (m_sourceFile.eof())
                            {
                                errorHandling("The closing tag for the comment in the line[" + std::to_string(currentLineNumber) + "] was not found");
                                break;
                            }
                        }
                        m_sourceFile.get(c);
                    }
                    else if (c == '/')
                    {
                        while (c != '\n')
                            m_sourceFile.get(c);
                        currentLineNumber++;
                        m_sourceFile.get(c);
                    }
                    else
                    {
                        m_sourceFile.get(c);
                        CS = IS_ERROR;
                    }
                }
                else
                {
                    m_sourceFile.get(c);
                    CS = IS_ERROR;
                }

                break;
            }
            case IS_IDENTIFIER:
            {
                std::string buf(1, c);
                m_sourceFile.get(c);

                while (((c >= 'A') && (c <= 'Z')) || ((c >= 'a') &&
                    (c <= 'z')) || ((c >= '0') && (c <= '9')) ||
                    (c == '_'))
                {
                    buf += c;
                    m_sourceFile.get(c);
                }

                if (m_keyWords.contains(buf))
                {
                    token.setName(KEYWORD);

                    if (buf == "int")
                        specifierStack.push(buf);
                }
                else
                {
                    if (!m_identifiers.contains(buf))
                    {
                        token.setName(NEW_IDENTIFIER);

                        Identifier idn(buf);

                        if (specifierStack.top() == "int")
                            idn.setSpecifier(INT);

                        if (c == '(')
                            idn.setType(FUNCTION);
                        else
                            idn.setType(VARIABLE);

                        m_identifiers.add(idn);
                    }
                    else
                        token.setName(IDENTIFIER);
                }

                token.setValue(buf);
                token.setLine(currentLineNumber);

                c == '\r' ? token.setIsLastInLine(true) : token.setIsLastInLine(false);

                m_tokenTable.add(token);
                CS = IS_START;

                break;
            }
            case IS_NUMBER:
            {
                std::string buf(1, c);
                m_sourceFile.get(c);

                if (((c >= 'A') && (c <= 'Z')) || ((c >= 'a') && (c <= 'z')) || (c == '_'))
                {
                    CS = IS_ERROR;
                    m_sourceFile.get(c);
                }
                else
                {
                    while ((c >= '0') && (c <= '9'))
                    {
                        buf += c;
                        m_sourceFile.get(c);
                    }

                    token.setName(CONSTANT);
                    token.setValue(buf);
                    token.setLine(currentLineNumber);

                    c == '\r' ? token.setIsLastInLine(true) : token.setIsLastInLine(false);

                    m_tokenTable.add(token);

                    Literal lt(buf, INTEGER_LITERAL);
                    m_literals.add(lt);

                    CS = IS_START;
                }

                break;
            }
            case IS_SEPARATOR:
            {
                std::string str(1, c);

                if (m_separators.contains(str))
                {
                    token.setName(SEPARATOR);
                    token.setValue(str);
                    token.setLine(currentLineNumber);

                    if (m_sourceFile.get(c))
                    {
                        m_sourceFile.seekg(-2, std::ios::cur);

                        c == '\r' ? token.setIsLastInLine(true) : token.setIsLastInLine(false);

                        m_sourceFile.get(c);
                    }
                    else
                        token.setIsLastInLine(true);

                    m_tokenTable.add(token);

                    if (c == '(')
                    {
                        m_sourceFile.get(c);

                        std::string msg;

                        msg = "The closing tag for the ( in the line[" + std::to_string(currentLineNumber) + "] was not found";
                        checkCloseTag('(', ')', c, msg, currentLineNumber);

                    }
                    else if (c == '{')
                    {
                        m_sourceFile.get(c);

                        std::string msg;

                        msg = "The closing tag for the { in the line[" + std::to_string(currentLineNumber) + "] was not found";
                        checkCloseTag('{', '}', c, msg, currentLineNumber);
                    }

                    m_sourceFile.get(c);

                    CS = IS_START;
                }
                else if (m_operators.contains(str))
                {
                    m_sourceFile.get(c);

                    if (c == '=')
                    {
                        str += c;
                        m_sourceFile.get(c);
                    }

                    c == '\r' ? token.setIsLastInLine(true) : token.setIsLastInLine(false);

                    token.setName(OPERATOR);
                    token.setValue(str);
                    token.setLine(currentLineNumber);
                    m_tokenTable.add(token);

                    CS = IS_START;
                }

                break;
            }
            case IS_ERROR:
            {
                errorHandling("Unknown character in line[" + std::to_string(currentLineNumber) + "]");
                CS = IS_START;

                break;
            }
        }
    }

    m_sourceFile.close();
    m_errors.close();
}

void LexicalAnalyzer::errorHandling(std::string errorText)
{
    m_success = false;
    printErrorMessageInFile(errorText);
}

void LexicalAnalyzer::printErrorMessageInFile(std::string errorText)
{
    std::string errorMsg;

    errorMsg += "--------------------------------\n";
    errorMsg += "Error type: lexical error.\n";
    errorMsg += "Error text: " + errorText + ".\n";
    errorMsg += "--------------------------------";
    errorMsg += "\n";

    m_errors << errorMsg;
}

void LexicalAnalyzer::checkCloseTag(char openTag, char closeTag, char currentChar, std::string errorMsg, int currentStringNumber)
{
    Token token;
    char c;

    if (currentChar != closeTag) // if next to the open tag symbol isn't the close tag
    {
        int offset = 1;
        int countOpenBrakets = 1;
        bool isEof = false;

        // search in the source program file all close tags for opened tags
        while (countOpenBrakets != 0)
        {
            m_sourceFile.get(c);

            if (c == closeTag)
                countOpenBrakets--;
            if (c == openTag)
                countOpenBrakets++;

            // if went to the end of the source program file but don't meet close tag is error
            if (m_sourceFile.eof())
            {
                errorHandling(errorMsg);
                isEof = true;
                break;
            }

            offset++;
        }

        // move to the place where started searching for the first closing tag
        if (!isEof)
            m_sourceFile.seekg(-offset, std::ios::cur);
    }
    else
    {
        std::string str(1, closeTag);

        token.setName(SEPARATOR);
        token.setValue(str);
        token.setLine(currentStringNumber);

        if (m_sourceFile.get(c))
        {
            m_sourceFile.seekg(-2, std::ios::cur);

            c == '\r' ? token.setIsLastInLine(true) : token.setIsLastInLine(false);

            m_sourceFile.get(c);
        }
        else
            token.setIsLastInLine(true);

        m_tokenTable.add(token);
    }
}
