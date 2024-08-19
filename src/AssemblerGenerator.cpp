#include "AssemblerGenerator.h"
#include "DynamicTable.h"
#include "Identifier.h"
#include "Literal.h"

#include <cstdlib>
#include <iosfwd>
#include <iostream>
#include <string>
#include <vector>

AssemblerGenerator::AssemblerGenerator(
    std::vector<std::string>& labels,
    std::vector<std::string>& postfix,
    DynamicTable<Identifier>& identifiers,
    DynamicTable<Literal>& literals,
    std::string asmCodeFile,
    std::string operandsNumberFile) :
    m_labels(labels),
    m_postfix(postfix),
    m_identifiers(identifiers),
    m_literals(literals)
{
    m_asmCode.open(asmCodeFile);

    std::ifstream oprNum;
    oprNum.open(operandsNumberFile);
    
    // checking if file with number of operator operands is open
    if (!oprNum.is_open())
    {
        size_t num = operandsNumberFile.find_last_of("\\");
        std::string name = operandsNumberFile.substr(num + 1, operandsNumberFile.size() - num);

        std::cout << "Failed to open file " << name << std::endl;
        system("pause");
        exit(0);
    }

    std::string str;
    int num;

    // if file is successfully opened reading the data into an associative array
    while (oprNum >> str >> num)
        m_operandsNumber[str] = num;
}

void AssemblerGenerator::generateAssembler()
{
    generateAssemblerInitSection();
    generateAssemblerDataSection();
    generateAssemblerCodeSection();
}

void AssemblerGenerator::generateAssemblerInitSection()
{
    m_asmCode << ".386\n";
    m_asmCode << ".MODEL FLAT, STDCALL\n";
    m_asmCode << "OPTION CASEMAP: NONE\n";
    m_asmCode << "EXTERN  ExitProcess@4: PROC\n\n";
}

void AssemblerGenerator::generateAssemblerDataSection()
{
    auto& table = m_identifiers.getTable();
    m_asmCode << ".DATA\n";

    for (auto& el : table)
    {
        if (el.getType() == VARIABLE && el.getSpecifier() == INT)
            m_asmCode << el.getName() << " DD " << "?\n";
    }

    m_asmCode << "r1" << " DD " << "?\n";
    m_asmCode << "r2" << " DD " << "?\n\n";
}

void AssemblerGenerator::generateAssemblerCodeSection()
{
    makeLabelsTransitions(); // for every label ("m*") create transition label ("m*:")

    m_asmCode << ".CODE\n";
    m_asmCode << "MAIN PROC\n\n";

    m_postfix.erase(m_postfix.end() - 3, m_postfix.end()); // delete from postfix notation array "0 return [int main()]"

    std::string logicalOperationResult;
    std::vector<operand> operandsStack;
    int i = 0;
    int j = 1;

    std::string element;

    // generating assembler program from postfix notation by operators template function
    for (int k = 0; k < m_postfix.size(); k++)
    {
        element = m_postfix[k];
        auto oprNumIter = m_operandsNumber.find(element);

        if (m_literals.contains(element) || m_identifiers.contains(element) || std::find(m_labels.begin(), m_labels.end(), element) != m_labels.end())
        {
            operand op(element, false, -1);
            operandsStack.push_back(op);
            i++;
        }
        else if (std::find(m_labelsTransitions.begin(), m_labelsTransitions.end(), element) != m_labelsTransitions.end())
        {
            makeLabel(element);
        }
        else if (oprNumIter != m_operandsNumber.end())
        {
            int k = (*oprNumIter).second;
            int minNumber = 1000000;

            for (int ind = i - k; ind <= i - 1; ind++)
            {
                if (operandsStack[ind].isWorkingVariable == true && operandsStack[ind].number <= minNumber)
                    minNumber = operandsStack[ind].number;
            }

            if (minNumber == 1000000)
                minNumber = j;

            if (element == "+")
                addOperator(operandsStack[i - k].value, operandsStack[i - 1].value, "r" + std::to_string(minNumber));
            else if (element == "-")
                subOperator(operandsStack[i - k].value, operandsStack[i - 1].value, "r" + std::to_string(minNumber));
            else if (element == "*")
                multOperator(operandsStack[i - k].value, operandsStack[i - 1].value, "r" + std::to_string(minNumber));
            else if (element == "=")
                assignmentOperator(operandsStack[i - k].value, operandsStack[i - 1].value);
            else if (element == "==")
                equilOperator(operandsStack[i - k].value, operandsStack[i - 1].value, logicalOperationResult);
            else if (element == "!=")
                notEquilOperator(operandsStack[i - k].value, operandsStack[i - 1].value, logicalOperationResult);
            else if (element == "<")
                lessOperator(operandsStack[i - k].value, operandsStack[i - 1].value, logicalOperationResult);
            else if (element == "if")
                ifOperator(operandsStack[i - k].value, operandsStack[i - 1].value);
            else if (element == "else")
                elseOperator(operandsStack[i - k].value);

            if (element == "if" || element == "else" || element == "=")
            {
                int offset = i - k;

                operandsStack.erase(operandsStack.begin() + offset);

                if (element != "else")
                    operandsStack.erase(operandsStack.begin() + offset);

                i = i - k;
                j = minNumber;
            }
            else if (element == "==" || element == "!=" || element == "<")
            {
                operand op(logicalOperationResult, false, -1);
                operandsStack[i - k] = op;
                operandsStack.erase(operandsStack.begin() + i - 1);

                i = i - k + 1;
                j = 1;
            }
            else
            {
                operand op("r" + std::to_string(minNumber), true, minNumber);
                operandsStack[i - k] = op;
                operandsStack.erase(operandsStack.begin() + i - 1);

                i = i - k + 1;
                j = minNumber + 1;
            }
        }
    }

    m_asmCode << "PUSH 0\n";
    m_asmCode << "CALL ExitProcess@4\n\n";
    m_asmCode << "MAIN ENDP\n";
    m_asmCode << "END MAIN\n";

    m_asmCode.close();
}

void AssemblerGenerator::assignmentOperator(std::string source, std::string dest)
{
    m_asmCode << "mov" << " " << "EAX" << ", " << dest << "\n";
    m_asmCode << "mov" << " " << source << ", " << "EAX" << "\n\n";
}

void AssemblerGenerator::addOperator(std::string operand1, std::string operand2, std::string result)
{
    m_asmCode << "mov" << " " << "EAX" << ", " << operand1 << "\n";
    m_asmCode << "mov" << " " << "EBX" << ", " << operand2 << "\n";
    m_asmCode << "add" << " " << "EAX" << ", " << "EBX" << "\n";
    m_asmCode << "mov" << " " << result << ", " << "EAX" << "\n\n";
}

void AssemblerGenerator::subOperator(std::string operand1, std::string operand2, std::string result)
{
    m_asmCode << "mov" << " " << "EAX" << ", " << operand1 << "\n";
    m_asmCode << "mov" << " " << "EBX" << ", " << operand2 << "\n";
    m_asmCode << "sub" << " " << "EAX" << ", " << "EBX" << "\n";
    m_asmCode << "mov" << " " << result << ", " << "EAX" << "\n\n";
}

void AssemblerGenerator::multOperator(std::string operand1, std::string operand2, std::string result)
{
    m_asmCode << "mov" << " " << "EAX" << ", " << operand1 << "\n";
    m_asmCode << "mov" << " " << "EBX" << ", " << operand2 << "\n";
    m_asmCode << "mul" << " " << "EBX" << "\n";
    m_asmCode << "mov" << " " << result << ", " << "EAX" << "\n\n";
}

void AssemblerGenerator::equilOperator(std::string operand1, std::string operand2, std::string& result)
{
    m_asmCode << "mov" << " " << "EAX" << ", " << operand1 << "\n";
    m_asmCode << "mov" << " " << "EBX" << ", " << operand2 << "\n";
    m_asmCode << "cmp" << " " << "EAX" << ", " << "EBX" << "\n";
    result = "jne";
}

void AssemblerGenerator::notEquilOperator(std::string operand1, std::string operand2, std::string& result)
{
    m_asmCode << "mov" << " " << "EAX" << ", " << operand1 << "\n";
    m_asmCode << "mov" << " " << "EBX" << ", " << operand2 << "\n";
    m_asmCode << "cmp" << " " << "EAX" << ", " << "EBX" << "\n";
    result = "je";
}

void AssemblerGenerator::lessOperator(std::string operand1, std::string operand2, std::string& result)
{
    m_asmCode << "mov" << " " << "EAX" << ", " << operand1 << "\n";
    m_asmCode << "mov" << " " << "EBX" << ", " << operand2 << "\n";
    m_asmCode << "cmp" << " " << "EAX" << ", " << "EBX" << "\n";
    result = "jnb";
}

void AssemblerGenerator::ifOperator(std::string logicalOperator, std::string label)
{
    m_asmCode << logicalOperator << " " << label << "\n";
}

void AssemblerGenerator::elseOperator(std::string label)
{
    m_asmCode << "jmp" << " " << label << "\n";
}

void AssemblerGenerator::makeLabel(std::string label)
{
    m_asmCode << label << "\n";
}

void AssemblerGenerator::makeLabelsTransitions()
{
    for (auto& label : m_labels)
        m_labelsTransitions.push_back(label + ":");
}
