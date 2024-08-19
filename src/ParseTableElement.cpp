#include "ParseTableElement.h"
#include "Token.h"

#include <string>

bool ParseTableElement::isTerminalsContain(Token token)
{
    for (int i = 0; i < m_terminals.size(); i++)
    {
        std::string currentTerm = m_terminals[i];
        std::string tokenName = token.getStringName(token.getName());
        std::string tokenValue = token.getValue();

        if (currentTerm == tokenName || currentTerm == tokenValue)
            return true;
    }

    return false;
}
