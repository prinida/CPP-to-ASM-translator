#ifndef LEXICAL_ANALYZER_H
#define LEXICAL_ANALYZER_H

#include "DynamicTable.h"
#include "Identifier.h"
#include "Literal.h"
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
        DynamicTable<Identifier>& _identifiers,
        DynamicTable<Literal>& _literals,
        DynamicTable<Token>& _tokenTable,
        std::string programFile,
        std::string errorsFile);
    void doLexicalAnalysis(); // �������, ��� ������ ������� �������������� ����������� ������
    void errorHandling(std::string errorText); // ��������� ������
    void printErrorMessageInFile(std::string errorText); // ��������������� ����� ������ � ���� ������
    bool getResult() { return success; } // �������� ��������� ������ ������������ ����������� (���� ������ ��� ���)

private:
    void checkCloseTag(char openTag, char closeTag, char currentChar, std::string errorMsg, int currentStringNumber); // �������, ������ ��� �������� �� �������� ���� �������� �����

    StaticTable<char>& alphabet; // ����������� ������� �������� �����
    StaticTable<std::string>& keyWords; // ����������� ������� �������� ���� �����
    StaticTable<std::string>& operators; // ����������� ������� ���������� �����
    StaticTable<std::string>& separators; // ����������� ������� ������������ �����

    DynamicTable<Identifier>& identifiers; // ����������� ������� ���������������
    DynamicTable<Literal>& literals; // ����������� ������� ����������� ��������

    DynamicTable<Token>& tokenTable; // ������� �������

    std::ifstream sourceFile; // ���� �������� ���������
    std::ofstream errors; // ���� ������

    bool success = true; // ����� ������������ �������
};

#endif
