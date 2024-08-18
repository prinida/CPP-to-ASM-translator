#ifndef IDENTIFIER_H
#define IDENTIFIER_H

#include "Enums.h"

#include <string>

class Identifier
{
public:
    Identifier(std::string _name = "", typeSpecifiers _specifier = INT, identifiersTypes _type = VARIABLE);

    void setName(std::string newName);
    void setType(identifiersTypes newType);
    void setSpecifier(typeSpecifiers newSpecifier);

    std::string getName();
    identifiersTypes getType();
    typeSpecifiers getSpecifier();

    friend bool operator==(const Identifier& left, const Identifier& right);
private:
    std::string name;
    identifiersTypes type;
    typeSpecifiers specifier;
};

#endif
