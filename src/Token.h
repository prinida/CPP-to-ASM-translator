#ifndef TOKEN_H
#define TOKEN_H

#include "Enums.h"

#include <string>

// ����� ������
class Token
{
public:
    void setTokenName(tokenNames name) { tokenName = name; };
    void setTokenValue(std::string value) { tokenValue = value; };
    void setTokenLine(unsigned int line) { tokenLine = line; };
    void setIsTokenLastInLine(bool isLast) { isTokenLastInLine = isLast; };

    tokenNames getTokenName() { return tokenName; };
    std::string getTokenValue() { return tokenValue; };
    unsigned int getTokenLine() { return tokenLine; };
    bool getIsTokenLastInLine() { return isTokenLastInLine; };

    std::string getTokenStringName(tokenNames name); // �������� ��� ������ � ���� ������

    bool isEmptyToken = false; // ������ �� �����

private:
    tokenNames tokenName; // ��� ������ (��� ������ ��� � enum)
    std::string tokenValue; // �������� ������ (�� ��� ����� ������)
    unsigned int tokenLine; // ������ � ������� ����� ����� � �������� ���������
    bool isTokenLastInLine = false; // �������� �� ����� ��������� � ������
};

#endif TOKEN_H
