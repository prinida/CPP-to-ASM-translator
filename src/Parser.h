#ifndef PARSER_H
#define PARSER_H

#include "DynamicTable.h"
#include "ParseTableElement.h"

#include <fstream>
#include <map>
#include <vector>

// ����� ��������������� ����������� (�������)
class Parser
{
public:
    Parser(DynamicTable<Token>& _tokenTable,
        std::map<unsigned int, ParseTableElement>& _parseTable,
        std::string _errorsFile,
        std::string _prioritiesFile,
        std::string _postfixFile);
    void doParse(); // ��������� �������������� ������
    void makePostfix(); // ������� ����������� ������ �� ��������� 
    void printErrorMessageInFile(std::string errorText, std::vector<std::string> possibleFixes); // ��������������� ����� ������ � ���� ������
    std::vector<std::string>& getPostfix() { return postfix; } // �������� ������ �� ������ � ����������� �������
    bool getSyntaxResult() { return success; } // �������� ��������� ������ ��������������� ����������� (���� ������ ��� ���)
    std::vector<std::string>& getLabels() { return labels; }; // �������� ������ �� ������ ����� (��� ��������� ������������� ����)

private:
    DynamicTable<Token>& tokenTable; // ������� �������
    std::map<unsigned int, ParseTableElement>& parseTable; // ������� �������

    std::ofstream errors; // ���� ������
    std::ofstream postfixFile; // ���� ����������� ������

    std::map<std::string, int> priorities; // ������������� ������ ����������� ���������� � �������� ����
    std::vector<std::string> infix; // ��������� ������
    std::vector<std::string> infixValue; // ������, ���������� �������� �������
    std::vector<std::string> postfix; // ����������� ������
    std::vector<std::string> labels; // ������ ����� (��� ��������� ������������� ����)

    bool success = true; // ������� �� �������������� ������
};

#endif