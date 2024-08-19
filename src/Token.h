#ifndef TOKEN_H
#define TOKEN_H

#include "Enums.h"

#include <string>

// класс токена
class Token
{
public:
    std::string getStringName(tokenNames name); // получить имя токена в виде строки

    void setName(tokenNames name) { m_name = name; };
    void setValue(std::string value) { m_value = value; };
    void setLine(unsigned int line) { m_line = line; };
    void setIsLastInLine(bool isLast) { m_isLastInLine = isLast; };

    tokenNames getName() { return m_name; };
    std::string getValue() { return m_value; };
    unsigned int getLine() { return m_line; };
    bool getIsLastInLine() { return m_isLastInLine; };

    friend bool operator==(const Token& left, const Token& right) { return left.m_value == right.m_value; };

private:
    tokenNames m_name; // имя токена (тип токена как в enum)
    std::string m_value; // значение токена (то что токен хранит)
    unsigned int m_line; // строка в которой токен стоит в исходной программе
    bool m_isLastInLine = false; // является ли токен последним в строке
};

#endif TOKEN_H
