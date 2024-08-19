#ifndef PARSER_H
#define PARSER_H

#include "DynamicTable.h"
#include "ParseTableElement.h"
#include "Token.h"

#include <fstream>
#include <iosfwd>
#include <map>
#include <string>
#include <vector>

// ����� ��������������� ����������� (�������)
class Parser
{
public:
    Parser(DynamicTable<Token>& tokenTable,
        std::map<unsigned int, ParseTableElement>& parseTable,
        std::string errorsFile,
        std::string prioritiesFile,
        std::string postfixFile);
    void doParse(); // ��������� �������������� ������

    std::vector<std::string>& getPostfix() { return m_postfix; } // �������� ������ �� ������ � ����������� �������
    bool getResult() { return m_success; } // �������� ��������� ������ ��������������� ����������� (���� ������ ��� ���)
    std::vector<std::string>& getLabels() { return m_labels; }; // �������� ������ �� ������ ����� (��� ��������� ������������� ����)

private:
    void makePostfix(); // ������� ����������� ������ �� ��������� 
    void errorHandling(std::string errorText, std::vector<std::string> possibleFixes); // ��������� ������
    void printErrorMessageInFile(std::string errorText, std::vector<std::string> possibleFixes); // ��������������� ����� ������ � ���� ������

    DynamicTable<Token>& m_tokenTable; // ������� �������
    std::map<unsigned int, ParseTableElement>& m_parseTable; // ������� �������

    std::ofstream m_errors; // ���� ������
    std::ofstream m_postfixFile; // ���� ����������� ������

    std::map<std::string, int> m_priorities; // ������������� ������ ����������� ���������� � �������� ����
    std::vector<std::string> m_infix; // ��������� ������
    std::vector<std::string> m_infixValue; // ������, ���������� �������� �������
    std::vector<std::string> m_postfix; // ����������� ������
    std::vector<std::string> m_labels; // ������ ����� (��� ��������� ������������� ����)

    bool m_success = true; // ������� �� �������������� ������
};

#endif