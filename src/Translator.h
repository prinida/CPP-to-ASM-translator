#ifndef TRANSLATOR_H
#define TRANSLATOR_H

#include "DynamicTable.h"
#include "Identifier.h"
#include "Literal.h"
#include "StaticTable.h"
#include "Token.h"

#include <string>

// ����� �����������
class Translator
{
public:
    Translator(StaticTable<char>& alphabet,
        StaticTable<std::string>& keyWords,
        StaticTable<std::string>& operators,
        StaticTable<std::string>& separators,
        DynamicTable<Identifier>& identifiers,
        DynamicTable<Literal>& literals,
        DynamicTable<Token>& tokenTable,
        std::string programFileName,
        std::string errorsFileName,
        std::string prioritiesFileName,
        std::string parseTableFileName,
        std::string postfixFileName,
        std::string asmCodeFileName,
        std::string operandsNumberFileName);

    void doTranslate(); // ��������� ����������

    std::string getResultMessage() { return m_resultMsg; }; // �������� ��������� � ����������� ������ �����������

private:
    StaticTable<char>& m_alphabet; // ����������� ������� �������� �����
    StaticTable<std::string>& m_keyWords; // ����������� ������� �������� ���� �����
    StaticTable<std::string>& m_operators; // ����������� ������� ���������� �����
    StaticTable<std::string>& m_separators; // ����������� ������� ������������ �����

    DynamicTable<Identifier>& m_identifiers; // ����������� ������� ���������������
    DynamicTable<Literal>& m_literals; // ����������� ������� ����������� ��������
    DynamicTable<Token>& m_tokenTable; // ������� �������

    std::string m_programFileName; // ��� ����� ���������
    std::string m_errorsFileName; // ��� ����� ������
    std::string m_prioritiesFileName; // ��� ����� ����������� ���������� � �������� ����
    std::string m_parseTableFileName; // ��� ����� ������� �������
    std::string m_postfixFileName; // ��� ����� ����������� ������
    std::string m_asmCodeFileName; // ��� ����� ������������� ����
    std::string m_operandsNumberFileName; // ��� �����, � ������� �������� ���������� ��������� � ���������

    std::string m_resultMsg; // ���������, ���������� ��������� ������ �����������
};

#endif
