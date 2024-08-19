#ifndef ENUMS_H
#define ENUMS_H

enum states { IS_START, IS_IDENTIFIER, IS_NUMBER, IS_SEPARATOR, IS_ERROR }; // finite state machine states
enum tokenNames { KEYWORD, IDENTIFIER, NEW_IDENTIFIER, CONSTANT, OPERATOR, SEPARATOR }; // token types
enum identifiersTypes { VARIABLE, FUNCTION, ARRAY }; // identifiers types (supported only variables)
enum typeSpecifiers { INT, FLOAT, DOUBLE }; // types specifiers (supported only int)
enum literalsType { INTEGER_LITERAL, FLOAT_LITERAL, DOUBLE_LITERAL, CHARACTER_LITERAL, STRING_LITERAL }; // literals types (supported only integer)

#endif
