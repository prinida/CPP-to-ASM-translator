#ifndef LITERAL_H
#define LITERAL_H

#include "Enums.h"

#include <string>

// literal class (integer literals etc.)
class Literal
{
public:
    Literal(std::string name = "", literalsType type = INTEGER_LITERAL) : m_name(name), m_type(type) {};

    void setName(std::string name) { m_name = name; };
    void setType(literalsType type) { m_type = type; };

    std::string getName() { return m_name; };
    literalsType getType() { return  m_type; };

    friend bool operator == (const Literal& left, const Literal& right) { return left.m_name == right.m_name; };

private:
    std::string m_name; // literal name
    literalsType m_type; // literal type
};

#endif
