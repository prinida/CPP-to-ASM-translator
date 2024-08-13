#ifndef LEXICAL_ANALYZER_H
#define LEXICAL_ANALYZER_H

#include "DynamicTable.h"
#include "StaticTable.h"

#include "Token.h"
#include <string>

// ����� ������������ �������
class LexicalAnalyzer
{
public:
    LexicalAnalyzer(StaticTable<char>& _alphabet,
        StaticTable<std::string>& _keyWords,
        StaticTable<std::string>& _operators,
        StaticTable<std::string>& _separators,
        DynamicTable<std::string>& _identifiers,
        DynamicTable<std::string>& _literals,
        DynamicTable<Token>& _tokenTable,
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

    DynamicTable<std::string>& identifiers; // ����������� ������� ���������������
    DynamicTable<std::string>& literals; // ����������� ������� ����������� ��������

    DynamicTable<Token>& tokenTable; // ������� �������

    std::ifstream sourceFile; // ���� �������� ���������
    std::ofstream errors; // ���� ������
};

#endif
