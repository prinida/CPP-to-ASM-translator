#include "Enums.h"
#include "Identifier.h"

#include <string>

bool operator==(const Identifier& left, const Identifier& right)
{
    return left.name == right.name;
}

Identifier::Identifier(std::string _name, typeSpecifiers _specifier, identifiersTypes _type) :
    name(_name),
    specifier(_specifier),
    type(_type) { }

void Identifier::setName(std::string newName)
{
    name = newName;
}

void Identifier::setType(identifiersTypes newType)
{
    type = newType;
}

void Identifier::setSpecifier(typeSpecifiers newSpecifier)
{
    specifier = newSpecifier;
}

std::string Identifier::getName()
{
    return name;
}

identifiersTypes Identifier::getType()
{
    return type;
}

typeSpecifiers Identifier::getSpecifier()
{
    return specifier;
}
