#ifndef PARSE_TABLE_ELEMENT_H
#define PARSE_TABLE_ELEMENT_H

#include "Token.h"

#include <string>
#include <vector>

// класс строки таблицы разбора
class ParseTableElement
{
public:
    bool isTerminalsContain(Token token); // содержитьс€ ли данный токен в множестве направл€ющих символов

    void setTerminals(std::vector<std::string> terminals) { m_terminals = terminals; };
    void setJump(unsigned int jump) { m_jump = jump; };
    void setAccept(bool accept) { m_accept = accept; };
    void setStack(bool stack) { m_stack = stack; };
    void setError(bool error) { m_error = error; };

    std::vector<std::string> getTerminals() { return m_terminals; };
    unsigned int getJump() { return m_jump; };
    bool getAccept() { return m_accept; };
    bool getStack() { return m_stack; };
    bool getError() { return m_error; };

private:
    std::vector<std::string> m_terminals; // множество направл€ющих символов
    unsigned int m_jump; // номер следующего состо€ни€, если 0, то извлечь из стека
    bool m_accept; // переходить ли на следующий символ входной цепочки
    bool m_stack; // сохранить ли в стеке номер состо€ни€
    bool m_error; // выдавать ли ошибку, если символ не содержитс€ в множестве направл€ющих символов
};

#endif
