#ifndef ENUMS_H
#define ENUMS_H

enum states { IS_START, IS_IDENTIFIER, IS_NUMBER, IS_SEPARATOR, IS_ERROR }; // ��������� ��������� ��������
enum tokenNames { KEYWORD, IDENTIFIER, NEW_IDENTIFIER, CONSTANT, OPERATOR, SEPARATOR }; // ���� �������
enum identifiersTypes { VARIABLE, FUNCTION, ARRAY }; // ������������� ���������������
enum typeSpecifiers { INT, FLOAT, DOUBLE }; // ������������� �����
enum literalsType { INTEGER_LITERAL, FLOAT_LITERAL, DOUBLE_LITERAL, CHARACTER_LITERAL, STRING_LITERAL }; // ���� ���������

#endif
