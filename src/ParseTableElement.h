#ifndef PARSE_TABLE_ELEMENT_H
#define PARSE_TABLE_ELEMENT_H

#include "Token.h"

#include <string>
#include <vector>

// ����� ������ ������� �������
class ParseTableElement
{
public:
    bool isTerminalsContain(Token token); // ����������� �� ������ ����� � ��������� ������������ ��������

    void setTerminals(std::vector<std::string> terminals) { m_terminals = terminals; };
    void setJump(unsigned int jump) { m_jump = jump; };
    void setAccept(bool accept) { m_accept = accept; };
    void setStack(bool stack) { m_stack = stack; };
    void setError(bool error) { m_error = error; };

    std::vector<std::string> getTerminals() { return m_terminals; };
    unsigned int getJump() { return m_jump; };
    bool getAccept() { return m_accept; };
    bool getStack() { return m_stack; };
    bool getError() { return m_error; };

private:
    std::vector<std::string> m_terminals; // ��������� ������������ ��������
    unsigned int m_jump; // ����� ���������� ���������, ���� 0, �� ������� �� �����
    bool m_accept; // ���������� �� �� ��������� ������ ������� �������
    bool m_stack; // ��������� �� � ����� ����� ���������
    bool m_error; // �������� �� ������, ���� ������ �� ���������� � ��������� ������������ ��������
};

#endif
