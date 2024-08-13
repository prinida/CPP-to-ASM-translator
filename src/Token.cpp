#include "Token.h"

std::string Token::getTokenStringName(tokenNames name)
{
    switch (name)
    {
        case KEYWORD: return "KEYWORD";
        case IDENTIFIER: return "IDENTIFIER";
        case NEW_IDENTIFIER: return "NEW_IDENTIFIER";
        case CONSTANT: return "CONSTANT";
        case OPERATOR: return "OPERATOR";
        case SEPARATOR: return "SEPARATOR";
        default: return "";
    }
}

bool operator==(const Token& left, const Token& right)
{
    return left.tokenValue == right.tokenValue;
}
