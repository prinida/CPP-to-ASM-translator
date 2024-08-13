#ifndef LEXICAL_ANALYZER_H
#define LEXICAL_ANALYZER_H

#include "StaticTable.h"
#include "Table.h"
#include "TokenTable.h"

#include <fstream>
#include <string>

// ����� ������������ �������
class LexicalAnalyzer
{
public:
    LexicalAnalyzer(StaticTable<char>& _alphabet,
        StaticTable<std::string>& _keyWords,
        StaticTable<std::string>& _operators,
        StaticTable<std::string>& _separators,
        Table<std::string>& _identifiers,
        Table<std::string>& _literals,
        TokenTable& _tokenTable,
        std::string programFile,
        std::string errorsFile);
    void doLexicalAnalysis(); // �������, ��� ������ ������� �������������� ����������� ������
    void printErrorMessageInFile(std::string errorText); // ��������������� ����� ������ � ���� ������

private:
    void checkCloseTag(char openTag, char closeTag, char currentChar, std::string errorMsg, int currentStringNumber); // �������, ������ ��� �������� �� �������� ���� �������� �����

    StaticTable<char>& alphabet; // ����������� ������� �������� �����
    StaticTable<std::string>& keyWords; // ����������� ������� �������� ���� �����
    StaticTable<std::string>& operators; // ����������� ������� ���������� �����
    StaticTable<std::string>& separators; // ����������� ������� ������������ �����

    Table<std::string>& identifiers; // ����������� ������� ���������������
    Table<std::string>& literals; // ����������� ������� ����������� ��������

    TokenTable& tokenTable; // ������� �������

    std::ifstream sourceFile; // ���� �������� ���������
    std::ofstream errors; // ���� ������
};

#endif
