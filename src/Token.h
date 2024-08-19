#ifndef TOKEN_H
#define TOKEN_H

#include "Enums.h"

#include <string>

// ����� ������
class Token
{
public:
    std::string getStringName(tokenNames name); // �������� ��� ������ � ���� ������

    void setName(tokenNames name) { m_name = name; };
    void setValue(std::string value) { m_value = value; };
    void setLine(unsigned int line) { m_line = line; };
    void setIsLastInLine(bool isLast) { m_isLastInLine = isLast; };

    tokenNames getName() { return m_name; };
    std::string getValue() { return m_value; };
    unsigned int getLine() { return m_line; };
    bool getIsLastInLine() { return m_isLastInLine; };

    friend bool operator==(const Token& left, const Token& right) { return left.m_value == right.m_value; };

private:
    tokenNames m_name; // ��� ������ (��� ������ ��� � enum)
    std::string m_value; // �������� ������ (�� ��� ����� ������)
    unsigned int m_line; // ������ � ������� ����� ����� � �������� ���������
    bool m_isLastInLine = false; // �������� �� ����� ��������� � ������
};

#endif TOKEN_H
