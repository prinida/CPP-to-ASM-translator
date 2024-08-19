#include "Enums.h"
#include "Token.h"

#include <string>

std::string Token::getStringName(tokenNames name)
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
