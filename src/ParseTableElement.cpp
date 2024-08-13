#include "ParseTableElement.h"

bool ParseTableElement::isTerminalsContain(Token token)
{
    for (int i = 0; i < terminals.size(); i++)
    {
        std::string currentTerm = terminals[i];
        std::string tokenName = token.getTokenStringName(token.getTokenName());
        std::string tokenValue = token.getTokenValue();

        if (currentTerm == tokenName || currentTerm == tokenValue)
            return true;
    }

    return false;
}
