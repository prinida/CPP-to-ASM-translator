#ifndef IDENTIFIER_H
#define IDENTIFIER_H

#include "Enums.h"

#include <string>

// identifier class (variables, functions etc.)
class Identifier
{
public:
    Identifier(std::string name = "", typeSpecifiers specifier = INT, identifiersTypes type = VARIABLE) : m_name(name), m_specifier(specifier), m_type(type) {};

    void setName(std::string name) { m_name = name; };
    void setType(identifiersTypes type) { m_type = type; };
    void setSpecifier(typeSpecifiers specifier) { m_specifier = specifier; };

    std::string getName() { return m_name; };
    identifiersTypes getType() { return m_type; };
    typeSpecifiers getSpecifier() { return m_specifier; };

    friend bool operator==(const Identifier& left, const Identifier& right) { return left.m_name == right.m_name; };

private:
    std::string m_name; // identifier name
    typeSpecifiers m_specifier; // identifier specifier
    identifiersTypes m_type; // identifier type
};

#endif
