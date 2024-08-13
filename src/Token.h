#ifndef TOKEN_H
#define TOKEN_H

#include "Enums.h"

#include <string>

// класс токена
class Token
{
public:
    void setTokenName(tokenNames name) { tokenName = name; };
    void setTokenValue(std::string value) { tokenValue = value; };
    void setTokenLine(unsigned int line) { tokenLine = line; };
    void setIsTokenLastInLine(bool isLast) { isTokenLastInLine = isLast; };

    tokenNames getTokenName() { return tokenName; };
    std::string getTokenValue() { return tokenValue; };
    unsigned int getTokenLine() { return tokenLine; };
    bool getIsTokenLastInLine() { return isTokenLastInLine; };

    std::string getTokenStringName(tokenNames name); // получить имя токена в виде строки

    bool isEmptyToken = false; // пустой ли токен

private:
    tokenNames tokenName; // имя токена (тип токена как в enum)
    std::string tokenValue; // значение токена (то что токен хранит)
    unsigned int tokenLine; // строка в которой токен стоит в исходной программе
    bool isTokenLastInLine = false; // является ли токен последним в строке
};

#endif TOKEN_H
