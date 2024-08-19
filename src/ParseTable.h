#ifndef PARSE_TABLE_H
#define PARSE_TABLE_H

#include "ParseTableElement.h"

#include <map>
#include <string>

// ����� ������� �������
class ParseTable
{
public:
    ParseTable(std::string parseTableFileName); // ����������� ��� ���������� ����� ������� �������

    std::map<unsigned int, ParseTableElement>& getParseTable() { return m_parseTable; }; // �������� ������ �� ������� �������

private:
    std::map<unsigned int, ParseTableElement> m_parseTable; // ������� �������
};

#endif
