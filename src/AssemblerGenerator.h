#ifndef ASSEMBLER_GENERATOR_H
#define ASSEMBLER_GENERATOR_H

#include "DynamicTable.h"

#include <fstream>
#include <map>
#include <string>
#include <vector>

// ���������, ��� �������� ���������
struct operand
{
    operand(std::string _value, bool _isWorkingVariable, int _number) : value(_value), isWorkingVariable(_isWorkingVariable), number(_number) {} // �����������

    bool isWorkingVariable; // �������� �� ���������� ������������� ����������� �������������� ��������
    std::string value; // �������� ���������� ���� �� ��������
    int number; // ����� ����������, ������� �������� ������������� ����������� �������������� ��������
};

// ����� ��������� ������������� ����
class AssemblerGenerator
{
public:
    AssemblerGenerator(std::vector<std::string>& _labels, std::vector<std::string>& _postfix, DynamicTable<std::string>& _identifiers, DynamicTable<std::string>& _literals, std::string _asmCodeFile, std::string _operandsNumberFile); // �����������
    void generateAssemblerInitSection(); // ��������� ���������� ����� ������������ ���������
    void generateAssemblerDataSection(); // ��������� ����� ������ ������������ ���������
    void generateAssemblerCodeSection(); // ��������� ����� ���� ������������ ���������

    void assignmentOperator(std::string source, std::string dest); // ������ ��������� ������������ ��� ��������� ������������� ����
    void addOperator(std::string operand1, std::string operand2, std::string result); // ������ ��������� �������� ��� ��������� ������������� ����
    void subOperator(std::string operand1, std::string operand2, std::string result); // ������ ��������� ��������� ��� ��������� ������������� ����
    void multOperator(std::string operand1, std::string operand2, std::string result); // ������ ��������� ��������� ��� ��������� ������������� ����
    void equilOperator(std::string operand1, std::string operand2, std::string& result); // ������ ��������� ��������� ��� ��������� ������������� ����
    void notEquilOperator(std::string operand1, std::string operand2, std::string& result); // ������ ��������� �� ��������� ��� ��������� ������������� ����
    void lessOperator(std::string operand1, std::string operand2, std::string& result); // ������ ��������� ������ ��� ��������� ������������� ����
    void ifOperator(std::string logicalOperator, std::string label); // ������ ��������� ��� ��� ��������� ������������� ����
    void elseOperator(std::string label); // ������ ��������� �� ��� ��������� ������������� ����
    void makeLabel(std::string label); // ������� ��� ��������� ����� � ������������ ���
    void makeLabelsTransitions(); // ������� ��� ��������� ������� ����� ("m*:") �� ����� ("m*")

private:
    std::ofstream asmCode; // ���� � ������������ �����
    std::vector<std::string>& labels; // ������ �� ������ �����
    std::vector<std::string> labelsTransitions; // ������ ������� �����
    std::vector<std::string>& postfix; // ������ �� ������ � ����������� �������
    DynamicTable<std::string>& identifiers; // ������ �� ������� ���������������
    DynamicTable<std::string>& literals; // ������ �� ������� ��������
    std::map<std::string, int> operandsNumber; // ������������� ������, � ������� �������� ���������� ��������� � ���������
};
#endif