#ifndef ASSEMBLER_GENERATOR_H
#define ASSEMBLER_GENERATOR_H

#include "DynamicTable.h"
#include "Identifier.h"
#include "Literal.h"

#include <fstream>
#include <iosfwd>
#include <map>
#include <string>
#include <vector>

// struct for operands storage, used only in AssemblerGenerator class
struct operand
{
    operand(std::string _value, bool _isWorkingVariable, int _number) : value(_value), isWorkingVariable(_isWorkingVariable), number(_number) {}

    bool isWorkingVariable; // is a variable an intermediate result of an arithmetic or logic operation
    std::string value; // variable's name or value
    int number; // variable's number (variable is an intermediate result of an arithmetic or logic operation)
};

// class of assembler code generation
class AssemblerGenerator
{
public:
    AssemblerGenerator(
        std::vector<std::string>& labels,
        std::vector<std::string>& postfix,
        DynamicTable<Identifier>& identifiers,
        DynamicTable<Literal>& literals,
        std::string asmCodeFile,
        std::string operandsNumberFile);
    void generateAssembler(); // main function to generate all assembler blocks of code

private:
    void generateAssemblerInitSection(); // generating the initial block of an assembler program
    void generateAssemblerDataSection(); // generation the data block of an assembler program
    void generateAssemblerCodeSection(); // generation the code block of an assembler program

    void assignmentOperator(std::string source, std::string dest); // assignment operator template to generate assembly code
    void addOperator(std::string operand1, std::string operand2, std::string result); // addition operator template to generate assembly code
    void subOperator(std::string operand1, std::string operand2, std::string result); // subtraction operator template to generate assembly code
    void multOperator(std::string operand1, std::string operand2, std::string result); // multiplication operator template to generate assembly code
    void equilOperator(std::string operand1, std::string operand2, std::string& result); // equality operator template to generate assembly code
    void notEquilOperator(std::string operand1, std::string operand2, std::string& result); // inequality operator template to generate assembly code
    void lessOperator(std::string operand1, std::string operand2, std::string& result); // less than operator template to generate assembly code
    void ifOperator(std::string logicalOperator, std::string label); // CTF(conditional transition to false) operator template to generate assembly code
    void elseOperator(std::string label); // UT(unconditional transition) operator template to generate assembly code
    void makeLabel(std::string label); // inserting labels into assembly code

    void makeLabelsTransitions(); // generating target labels ("m*:") from labels ("m*")

    std::ofstream m_asmCode; // assembly program file

    std::vector<std::string>& m_labels; // reference to labels array
    std::vector<std::string> m_labelsTransitions; // target labels array
    std::vector<std::string>& m_postfix; // reference to postfix notation array

    DynamicTable<Identifier>& m_identifiers; // reference to identifiers table
    DynamicTable<Literal>& m_literals; // reference to literals table

    std::map<std::string, int> m_operandsNumber; // associative array for pairs "operator - number of operands"
};
#endif