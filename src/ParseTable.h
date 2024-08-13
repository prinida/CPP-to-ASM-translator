#ifndef PARSE_TABLE_H
#define PARSE_TABLE_H

#include "ParseTableElement.h"

#include <string>
#include <map>

// ����� ������� �������
class ParseTable
{
public:
    ParseTable(std::string parseTableFileName); // ����������� ��� ���������� ����� ������� �������
    std::map<unsigned int, ParseTableElement>& getParseTable() { return parseTable; }; // �������� ������ �� ������� �������

private:
    std::map<unsigned int, ParseTableElement> parseTable; // ������� �������
};

#endif
