#ifndef ENUMS_H
#define ENUMS_H

enum states { isSTART, isIDENTIFIER, isNUMBER, isSEPARATOR, isERROR }; // состояние конечного автомата
enum tokenNames { KEYWORD, IDENTIFIER, NEW_IDENTIFIER, CONSTANT, OPERATOR, SEPARATOR }; // типы токенов

#endif
