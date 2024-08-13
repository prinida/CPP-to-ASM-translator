#ifndef TOKEN_TABLE_H
#define TOKEN_TABLE_H

#include "Token.h"
#include "Enums.h"

#include <list>

// ����� ������� �������
class TokenTable
{
public:
    void add(Token value); // �������� ����� � �������
    void printTable(); // ���������� � ������� ������� �������
    std::string getTokenStringName(tokenNames name); // ��������� enum � string
    Token popToken(); // ������� ����� �� ������ ������� (�� ������ ������)

private:
    std::list<Token> table; // ������� �������
};

#endif 
