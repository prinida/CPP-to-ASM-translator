#ifndef ENUMS_H
#define ENUMS_H

enum states { IS_START, IS_IDENTIFIER, IS_NUMBER, IS_SEPARATOR, IS_ERROR }; // состояние конечного автомата
enum tokenNames { KEYWORD, IDENTIFIER, NEW_IDENTIFIER, CONSTANT, OPERATOR, SEPARATOR }; // типы токенов

#endif
