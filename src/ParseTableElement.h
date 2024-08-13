#ifndef PARSE_TABLE_ELEMENT_H
#define PARSE_TABLE_ELEMENT_H

#include "Token.h"

#include <vector>
#include <string>

// класс строки таблицы разбора
class ParseTableElement
{
public:
    bool isTerminalsContain(Token token); // содержитьс€ ли данный токен в множестве направл€ющих символов

    void setTerminals(std::vector<std::string> terminals) { this->terminals = terminals; };
    void setJump(unsigned int jump) { this->jump = jump; };
    void setAccept(bool accept) { this->accept = accept; };
    void setStack(bool stack) { this->stack = stack; };
    void setError(bool error) { this->error = error; };

    std::vector<std::string> getTerminals() { return terminals; };
    unsigned int getJump() { return jump; };
    bool getAccept() { return accept; };
    bool getStack() { return stack; };
    bool getError() { return error; };

private:
    std::vector<std::string> terminals; // множество направл€ющих символов
    unsigned int jump; // номер следующего состо€ни€, если 0, то извлечь из стека
    bool accept; // переходить ли на следующий символ входной цепочки
    bool stack; // сохранить ли в стеке номер состо€ни€
    bool error; // выдавать ли ошибку, если символ не содержитс€ в множестве направл€ющих символов
};

#endif
