#ifndef PARSE_TABLE_ELEMENT_H
#define PARSE_TABLE_ELEMENT_H

#include "Token.h"

#include <string>
#include <vector>

// parse table row class
class ParseTableElement
{
public:
    bool isTerminalsContain(Token token); // whether the given token is contained in a set of guide characters(terminals)

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
    std::vector<std::string> m_terminals; // set of guide characters
    unsigned int m_jump; // number of next state(row id in parse table), if zero pop element from stack
    bool m_accept; // whether to move to the next character in the input string
    bool m_stack; // whether to save the number of state(row id) in stack
    bool m_error; // whether to throw an error if a symbol(string) isn't contained in the set of guide characters(terminals)
};

#endif
