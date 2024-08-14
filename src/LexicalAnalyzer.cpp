#include "LexicalAnalyzer.h"

#include <iostream>
#include <string>

LexicalAnalyzer::LexicalAnalyzer(StaticTable<char>& _alphabet, StaticTable<std::string>& _keyWords, StaticTable<std::string>& _operators, StaticTable<std::string>& _separators, DynamicTable<std::string>& _identifiers, DynamicTable<std::string>& _literals, DynamicTable<Token>& _tokenTable, std::string programFile, std::string errorsFile) :
    alphabet(_alphabet),
    keyWords(_keyWords),
    operators(_operators),
    separators(_separators),
    identifiers(_identifiers),
    literals(_literals),
    tokenTable(_tokenTable)
{
    sourceFile.open(programFile, std::ios::binary);

    if (!sourceFile.is_open())
    {
        size_t num = programFile.find_last_of("\\");
        std::string name = programFile.substr(num + 1, programFile.size() - num);

        std::cout << "Failed to open file " << name << std::endl;
        system("pause");
        exit(0);
    }

    errors.open(errorsFile);
}

void LexicalAnalyzer::doLexicalAnalysis()
{
    char c;
    sourceFile.get(c);
    states CS = IS_START;
    Token token;
    int currentStringNumber = 1;

    while (!sourceFile.eof())
    {
        switch (CS)
        {
        case IS_START:
        {
            while ((c == ' ') || (c == '\t') || (c == '\n') || (c == '\r'))
            {
                if (c == '\n')
                    currentStringNumber++;

                sourceFile.get(c);
            }

            if (alphabet.contains(c))
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
                sourceFile.get(c);
                if (c == '*')
                {
                    std::string str;
                    sourceFile.get(c);
                    str += c;
                    sourceFile.get(c);
                    str += c;

                    while (str != "*/")
                    {
                        sourceFile.get(c);
                        std::swap(str[0], str[1]);
                        str[1] = c;

                        if (sourceFile.eof())
                        {
                            errorHandling("The closing tag for the comment in the line[" + std::to_string(currentStringNumber) + "] was not found");
                            break;
                        }
                    }
                    sourceFile.get(c);
                }
                else if (c == '/')
                {
                    while (c != '\n')
                        sourceFile.get(c);
                    currentStringNumber++;
                    sourceFile.get(c);
                }
                else
                {
                    sourceFile.get(c);
                    CS = IS_ERROR;
                }
            }
            else
            {
                sourceFile.get(c);
                CS = IS_ERROR;
            }

            break;
        }
        case IS_IDENTIFIER:
        {
            std::string buf(1, c);
            sourceFile.get(c);

            while (((c >= 'A') && (c <= 'Z')) || ((c >= 'a') &&
                (c <= 'z')) || ((c >= '0') && (c <= '9')) ||
                (c == '_'))
            {
                buf += c;
                sourceFile.get(c);
            }

            if (keyWords.contains(buf))
                token.setTokenName(KEYWORD);
            else
            {
                if (!identifiers.contains(buf))
                {
                    token.setTokenName(NEW_IDENTIFIER);
                    identifiers.add(buf);
                }
                else
                    token.setTokenName(IDENTIFIER);
            }

            token.setTokenValue(buf);
            token.setTokenLine(currentStringNumber);

            c == '\r' ? token.setIsTokenLastInLine(true) : token.setIsTokenLastInLine(false);

            tokenTable.add(token);
            CS = IS_START;

            break;
        }
        case IS_NUMBER:
        {
            std::string buf(1, c);
            sourceFile.get(c);

            if (((c >= 'A') && (c <= 'Z')) || ((c >= 'a') && (c <= 'z')) || (c == '_'))
            {
                CS = IS_ERROR;
                sourceFile.get(c);
            }
            else
            {
                while ((c >= '0') && (c <= '9'))
                {
                    buf += c;
                    sourceFile.get(c);
                }

                token.setTokenName(CONSTANT);
                token.setTokenValue(buf);
                token.setTokenLine(currentStringNumber);

                c == '\r' ? token.setIsTokenLastInLine(true) : token.setIsTokenLastInLine(false);

                tokenTable.add(token);
                literals.add(buf);
                CS = IS_START;
            }

            break;
        }
        case IS_SEPARATOR:
        {
            std::string str(1, c);

            if (separators.contains(str))
            {
                token.setTokenName(SEPARATOR);
                token.setTokenValue(str);
                token.setTokenLine(currentStringNumber);

                if (sourceFile.get(c))
                {
                    sourceFile.seekg(-2, std::ios::cur);

                    c == '\r' ? token.setIsTokenLastInLine(true) : token.setIsTokenLastInLine(false);

                    sourceFile.get(c);
                }
                else
                    token.setIsTokenLastInLine(true);

                tokenTable.add(token);

                if (c == '(')
                {
                    sourceFile.get(c);

                    std::string msg;

                    msg = "The closing tag for the ( in the line[" + std::to_string(currentStringNumber) + "] was not found";
                    checkCloseTag('(', ')', c, msg, currentStringNumber);

                }
                else if (c == '{')
                {
                    sourceFile.get(c);

                    std::string msg;

                    msg = "The closing tag for the { in the line[" + std::to_string(currentStringNumber) + "] was not found";
                    checkCloseTag('{', '}', c, msg, currentStringNumber);
                }

                sourceFile.get(c);

                CS = IS_START;
            }
            else if (operators.contains(str))
            {
                sourceFile.get(c);

                if (c == '=')
                {
                    str += c;
                    sourceFile.get(c);
                }

                c == '\r' ? token.setIsTokenLastInLine(true) : token.setIsTokenLastInLine(false);

                token.setTokenName(OPERATOR);
                token.setTokenValue(str);
                token.setTokenLine(currentStringNumber);
                tokenTable.add(token);

                CS = IS_START;
            }

            break;
        }
        case IS_ERROR:
        {
            errorHandling("Unknown character in line[" + std::to_string(currentStringNumber) + "]");
            CS = IS_START;

            break;
        }
        }
    }

    sourceFile.close();
    errors.close();
}

void LexicalAnalyzer::errorHandling(std::string errorText)
{
    success = false;
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

    errors << errorMsg;
}

void LexicalAnalyzer::checkCloseTag(char openTag, char closeTag, char currentChar, std::string errorMsg, int currentStringNumber)
{
    Token token;
    char c;

    if (currentChar != closeTag)
    {
        int offset = 1;
        int countOpenBrakets = 1;
        bool isEof = false;

        while (countOpenBrakets != 0)
        {
            sourceFile.get(c);

            if (c == closeTag)
                countOpenBrakets--;
            if (c == openTag)
                countOpenBrakets++;

            if (sourceFile.eof())
            {
                errorHandling(errorMsg);
                isEof = true;
                break;
            }

            offset++;
        }

        if (!isEof)
            sourceFile.seekg(-offset, std::ios::cur);
    }
    else
    {
        std::string str(1, closeTag);

        token.setTokenName(SEPARATOR);
        token.setTokenValue(str);
        token.setTokenLine(currentStringNumber);

        if (sourceFile.get(c))
        {
            sourceFile.seekg(-2, std::ios::cur);

            c == '\r' ? token.setIsTokenLastInLine(true) : token.setIsTokenLastInLine(false);

            sourceFile.get(c);
        }
        else
            token.setIsTokenLastInLine(true);

        tokenTable.add(token);
    }
}
