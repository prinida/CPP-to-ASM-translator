#ifndef TOKEN_H
#define TOKEN_H

#include "Enums.h"

#include <string>

// token class (filled by lexical analyzer and used by parser)
class Token
{
public:
    std::string getStringName(tokenNames name); // get token name as string

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
    tokenNames m_name; // token name(token type in enum)
    std::string m_value; // token value (what the token stores)
    unsigned int m_line; // line in which token appears in source program
    bool m_isLastInLine = false; // is the token the last one in the line
};

#endif TOKEN_H
