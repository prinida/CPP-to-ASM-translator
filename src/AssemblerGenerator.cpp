#include "AssemblerGenerator.h"

#include <iostream>

AssemblerGenerator::AssemblerGenerator(
    std::vector<std::string>& _labels,
    std::vector<std::string>& _postfix,
    DynamicTable<std::string>& _identifiers,
    DynamicTable<std::string>& _literals,
    std::string _asmCodeFile,
    std::string _operandsNumberFile) :
    labels(_labels),
    postfix(_postfix),
    identifiers(_identifiers),
    literals(_literals)
{
    asmCode.open(_asmCodeFile);

    std::ifstream oprNum;
    oprNum.open(_operandsNumberFile);

    if (!oprNum.is_open())
    {
        size_t num = _operandsNumberFile.find_last_of("\\");
        std::string name = _operandsNumberFile.substr(num + 1, _operandsNumberFile.size() - num);

        std::cout << "Failed to open file " << name << std::endl;
        system("pause");
        exit(0);
    }
    
    std::string str;
    int num;

    while (oprNum >> str >> num)
        operandsNumber[str] = num;
}

void AssemblerGenerator::generateAssemblerInitSection()
{
    asmCode << ".386\n";
    asmCode << ".MODEL FLAT, STDCALL\n";
    asmCode << "OPTION CASEMAP: NONE\n";
    asmCode << "EXTERN  ExitProcess@4: PROC\n\n";
}

void AssemblerGenerator::generateAssemblerDataSection()
{
    auto& table = identifiers.getTable();
    asmCode << ".DATA\n";

    for (auto& el : table)
    {
        if (el != "main")
            asmCode << el << " DD " << "?\n";
    }

    asmCode << "r1" << " DD " << "?\n";
    asmCode << "r2" << " DD " << "?\n\n";
}

void AssemblerGenerator::generateAssemblerCodeSection()
{
    makeLabelsTransitions();

    asmCode << ".CODE\n";
    asmCode << "MAIN PROC\n\n";

    postfix.erase(postfix.end() - 3, postfix.end());

    std::string logicalOperationResult;
    std::vector<operand> operandsStack;
    int i = 0;
    int j = 1;

    std::string element;

    for (int k = 0; k < postfix.size(); k++)
    {
        element = postfix[k];
        auto oprNumIter = operandsNumber.find(element);

        if (literals.contains(element) || identifiers.contains(element) || std::find(labels.begin(), labels.end(), element) != labels.end())
        {
            operand op(element, false, -1);
            operandsStack.push_back(op);
            i++;
        }
        else if (std::find(labelsTransitions.begin(), labelsTransitions.end(), element) != labelsTransitions.end())
        {
            makeLabel(element);
        }
        else if (oprNumIter != operandsNumber.end())
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

    asmCode << "PUSH 0\n";
    asmCode << "CALL ExitProcess@4\n\n";
    asmCode << "MAIN ENDP\n";
    asmCode << "END MAIN\n";

    asmCode.close();
}

void AssemblerGenerator::assignmentOperator(std::string source, std::string dest)
{
    asmCode << "mov" << " " << "EAX" << ", " << dest << "\n";
    asmCode << "mov" << " " << source << ", " << "EAX" << "\n\n";
}

void AssemblerGenerator::addOperator(std::string operand1, std::string operand2, std::string result)
{
    asmCode << "mov" << " " << "EAX" << ", " << operand1 << "\n";
    asmCode << "mov" << " " << "EBX" << ", " << operand2 << "\n";
    asmCode << "add" << " " << "EAX" << ", " << "EBX" << "\n";
    asmCode << "mov" << " " << result << ", " << "EAX" << "\n\n";
}

void AssemblerGenerator::subOperator(std::string operand1, std::string operand2, std::string result)
{
    asmCode << "mov" << " " << "EAX" << ", " << operand1 << "\n";
    asmCode << "mov" << " " << "EBX" << ", " << operand2 << "\n";
    asmCode << "sub" << " " << "EAX" << ", " << "EBX" << "\n";
    asmCode << "mov" << " " << result << ", " << "EAX" << "\n\n";
}

void AssemblerGenerator::multOperator(std::string operand1, std::string operand2, std::string result)
{
    asmCode << "mov" << " " << "EAX" << ", " << operand1 << "\n";
    asmCode << "mov" << " " << "EBX" << ", " << operand2 << "\n";
    asmCode << "mul" << " " << "EBX" << "\n";
    asmCode << "mov" << " " << result << ", " << "EAX" << "\n\n";
}

void AssemblerGenerator::equilOperator(std::string operand1, std::string operand2, std::string& result)
{
    asmCode << "mov" << " " << "EAX" << ", " << operand1 << "\n";
    asmCode << "mov" << " " << "EBX" << ", " << operand2 << "\n";
    asmCode << "cmp" << " " << "EAX" << ", " << "EBX" << "\n";
    result = "jne";
}

void AssemblerGenerator::notEquilOperator(std::string operand1, std::string operand2, std::string& result)
{
    asmCode << "mov" << " " << "EAX" << ", " << operand1 << "\n";
    asmCode << "mov" << " " << "EBX" << ", " << operand2 << "\n";
    asmCode << "cmp" << " " << "EAX" << ", " << "EBX" << "\n";
    result = "je";
}

void AssemblerGenerator::lessOperator(std::string operand1, std::string operand2, std::string& result)
{
    asmCode << "mov" << " " << "EAX" << ", " << operand1 << "\n";
    asmCode << "mov" << " " << "EBX" << ", " << operand2 << "\n";
    asmCode << "cmp" << " " << "EAX" << ", " << "EBX" << "\n";
    result = "jnb";
}

void AssemblerGenerator::ifOperator(std::string logicalOperator, std::string label)
{
    asmCode << logicalOperator << " " << label << "\n";
}

void AssemblerGenerator::elseOperator(std::string label)
{
    asmCode << "jmp" << " " << label << "\n";
}

void AssemblerGenerator::makeLabel(std::string label)
{
    asmCode << label << "\n";
}

void AssemblerGenerator::makeLabelsTransitions()
{
    for (auto& label : labels)
        labelsTransitions.push_back(label + ":");
}
