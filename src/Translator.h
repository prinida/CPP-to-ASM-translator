#ifndef TRANSLATOR_H
#define TRANSLATOR_H

#include "StaticTable.h"
#include "DynamicTable.h"

#include <string>

// ����� �����������
class Translator
{
public:
    Translator(StaticTable<char>& _alphabet,
        StaticTable<std::string>& _keyWords,
        StaticTable<std::string>& _operators,
        StaticTable<std::string>& _separators,
        DynamicTable<std::string>& _identifiers,
        DynamicTable<std::string>& _literals,
        DynamicTable<Token>& _tokenTable,
        std::string _programFileName,
        std::string _errorsFileName,
        std::string _prioritiesFileName,
        std::string _parseTableFileName,
        std::string _postfixFileName,
        std::string _asmCodeFileName,
        std::string _operandsNumberFileName);

    void doTranslate(); // ��������� ����������
    std::string getResultMessage(); // �������� ��������� � ����������� ������ �����������

private:
    StaticTable<char>& alphabet; // ����������� ������� �������� �����
    StaticTable<std::string>& keyWords; // ����������� ������� �������� ���� �����
    StaticTable<std::string>& operators; // ����������� ������� ���������� �����
    StaticTable<std::string>& separators; // ����������� ������� ������������ �����

    DynamicTable<std::string>& identifiers; // ����������� ������� ���������������
    DynamicTable<std::string>& literals; // ����������� ������� ����������� ��������
    DynamicTable<Token>& tokenTable; // ������� �������

    std::string programFileName; // ��� ����� ���������
    std::string errorsFileName; // ��� ����� ������
    std::string prioritiesFileName; // ��� ����� ����������� ���������� � �������� ����
    std::string parseTableFileName; // ��� ����� ������� �������
    std::string postfixFileName; // ��� ����� ����������� ������
    std::string asmCodeFileName; // ��� ����� ������������� ����
    std::string operandsNumberFileName; // ��� �����, � ������� �������� ���������� ��������� � ���������

    std::string resultMsg; // ���������, ���������� ��������� ������ �����������
};

#endif
