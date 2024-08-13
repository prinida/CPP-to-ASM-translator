#ifndef PARSE_TABLE_ELEMENT_H
#define PARSE_TABLE_ELEMENT_H

#include "Token.h"

#include <vector>
#include <string>

// ����� ������ ������� �������
class ParseTableElement
{
public:
    bool isTerminalsContain(Token token); // ����������� �� ������ ����� � ��������� ������������ ��������

    void setTerminals(std::vector<std::string> terminals) { this->terminals = terminals; };
    void setJump(unsigned int jump) { this->jump = jump; };
    void setAccept(bool accept) { this->accept = accept; };
    void setStack(bool stack) { this->stack = stack; };
    void setError(bool error) { this->error = error; };

    std::vector<std::string> getTerminals() { return terminals; };
    unsigned int getJump() { return jump; };
    bool getAccept() { return accept; };
    bool getStack() { return stack; };
    bool getError() { return error; };

private:
    std::vector<std::string> terminals; // ��������� ������������ ��������
    unsigned int jump; // ����� ���������� ���������, ���� 0, �� ������� �� �����
    bool accept; // ���������� �� �� ��������� ������ ������� �������
    bool stack; // ��������� �� � ����� ����� ���������
    bool error; // �������� �� ������, ���� ������ �� ���������� � ��������� ������������ ��������
};

#endif
