#ifndef TRANSLATOR_H
#define TRANSLATOR_H

#include "StaticTable.h"
#include "Table.h"
#include "TokenTable.h"
#include "LexicalAnalyzer.h"
#include "ParseTable.h"
#include "Parser.h"
#include "AssemblerGenerator.h"

#include <string>

// ����� �����������
class Translator
{
public:
    Translator(StaticTable<char>& _alphabet, 
        StaticTable<std::string>& _keyWords, 
        StaticTable<std::string>& _operators, 
        StaticTable<std::string>& _separators, 
        Table<std::string>& _identifiers, 
        Table<std::string>& _literals, 
        TokenTable& _tokenTable, 
        std::string _programFileName, 
        std::string _errorsFileName,
        std::string _prioritiesFileName, 
        std::string _parseTableFileName,
        std::string _postfixFileName,
        std::string _asmCodeFileName,
        std::string _operandsNumberFileName);

    void doTranslate(); // ��������� ����������

private:
    StaticTable<char>& alphabet; // ����������� ������� �������� �����
    StaticTable<std::string>& keyWords; // ����������� ������� �������� ���� �����
    StaticTable<std::string>& operators; // ����������� ������� ���������� �����
    StaticTable<std::string>& separators; // ����������� ������� ������������ �����

    Table<std::string>& identifiers; // ����������� ������� ���������������
    Table<std::string>& literals; // ����������� ������� ����������� ��������

    TokenTable& tokenTable; // ������� �������

    std::string programFileName; // ��� ����� ���������
    std::string errorsFileName; // ��� ����� ������
    std::string prioritiesFileName; // ��� ����� ����������� ���������� � �������� ����
    std::string parseTableFileName; // ��� ����� ������� �������
    std::string postfixFileName; // ��� ����� ����������� ������
    std::string asmCodeFileName; // ��� ����� ������������� ����
    std::string operandsNumberFileName; // ��� �����, � ������� �������� ���������� ��������� � ���������
};

#endif
