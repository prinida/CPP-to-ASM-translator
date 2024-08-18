#include "Literal.h"

Literal::Literal(std::string _name, literalsType _type) :
    name(_name),
    type(_type) { }

void Literal::setName(std::string newName)
{
    name = newName;
}

void Literal::setType(literalsType newType)
{
    type = newType;
}

std::string Literal::getName()
{
    return name;
}

literalsType Literal::getType()
{
    return type;
}

bool operator==(const Literal& left, const Literal& right)
{
    return left.name == right.name;
}
