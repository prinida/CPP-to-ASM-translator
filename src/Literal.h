#ifndef LITERAL_H
#define LITERAL_H

#include "Enums.h"

#include <string>

class Literal
{
public:
    Literal(std::string _name = "", literalsType _type = INTEGER_LITERAL);

    void setName(std::string newName);
    void setType(literalsType newType);

    std::string getName();
    literalsType getType();

    friend bool operator == (const Literal& left, const Literal& right);

private:
    std::string name;
    literalsType type;
};

#endif
