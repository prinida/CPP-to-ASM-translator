#include "TokenTable.h"

#include <iostream>

void TokenTable::add(Token value)
{
    table.push_back(value);
}

void TokenTable::printTable()
{
    for (Token el : table)
        std::cout << el.getTokenValue() << " " << getTokenStringName(el.getTokenName()) << " " << el.getTokenLine() << " " << el.getIsTokenLastInLine() << '\n';
}

std::string TokenTable::getTokenStringName(tokenNames name)
{
    switch (name)
    {
    case KEYWORD: return "KEYWORD";
    case IDENTIFIER: return "IDENTIFIER";
    case NEW_IDENTIFIER: return "NEW_IDENTIFIER";
    case CONSTANT: return "CONSTANT";
    case OPERATOR: return "OPERATOR";
    case SEPARATOR: return "SEPARATOR";
    }
}

Token TokenTable::popToken()
{
    if (table.size() != 0)
    {
        Token token = table.front();
        table.pop_front();

        return token;
    }
    else
    {
        Token token;
        token.isEmptyToken = true;

        return token;
    }
}