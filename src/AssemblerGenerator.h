#ifndef ASSEMBLER_GENERATOR_H
#define ASSEMBLER_GENERATOR_H

#include "DynamicTable.h"

#include <fstream>
#include <map>
#include <string>
#include <vector>

// структура, для хранения операндов
struct operand
{
    operand(std::string _value, bool _isWorkingVariable, int _number) : value(_value), isWorkingVariable(_isWorkingVariable), number(_number) {} // конструктор

    bool isWorkingVariable; // является ли переменная промежуточным результатом арифметической операции
    std::string value; // значение переменной либо ее название
    int number; // номер переменной, которая является промежуточным результатом арифметической операции
};

// класс генерации ассемблерного кода
class AssemblerGenerator
{
public:
    AssemblerGenerator(std::vector<std::string>& _labels, std::vector<std::string>& _postfix, DynamicTable<std::string>& _identifiers, DynamicTable<std::string>& _literals, std::string _asmCodeFile, std::string _operandsNumberFile); // конструктор
    void generateAssemblerInitSection(); // генерация начального блока ассемблерной программы
    void generateAssemblerDataSection(); // генерация блока данных ассемблерной программы
    void generateAssemblerCodeSection(); // генерация блока кода ассемблерной программы

    void assignmentOperator(std::string source, std::string dest); // шаблон оператора присваивания для генерации ассемблерного кода
    void addOperator(std::string operand1, std::string operand2, std::string result); // шаблон оператора сложения для генерации ассемблерного кода
    void subOperator(std::string operand1, std::string operand2, std::string result); // шаблон оператора вычитания для генерации ассемблерного кода
    void multOperator(std::string operand1, std::string operand2, std::string result); // шаблон оператора умножения для генерации ассемблерного кода
    void equilOperator(std::string operand1, std::string operand2, std::string& result); // шаблон оператора равенства для генерации ассемблерного кода
    void notEquilOperator(std::string operand1, std::string operand2, std::string& result); // шаблон оператора не равенства для генерации ассемблерного кода
    void lessOperator(std::string operand1, std::string operand2, std::string& result); // шаблон оператора меньше для генерации ассемблерного кода
    void ifOperator(std::string logicalOperator, std::string label); // шаблон оператора УПЛ для генерации ассемблерного кода
    void elseOperator(std::string label); // шаблон оператора БП для генерации ассемблерного кода
    void makeLabel(std::string label); // функция для занесения меток в ассемблерный код
    void makeLabelsTransitions(); // функция для генерации целевых меток ("m*:") из меток ("m*")

private:
    std::ofstream asmCode; // файл с ассемблерным кодом
    std::vector<std::string>& labels; // ссылка на массив меток
    std::vector<std::string> labelsTransitions; // массив целевых меток
    std::vector<std::string>& postfix; // ссылка на массив с постфиксной записью
    DynamicTable<std::string>& identifiers; // ссылка на таблицу идентификаторов
    DynamicTable<std::string>& literals; // ссылка на таблицу констант
    std::map<std::string, int> operandsNumber; // ассоциативный массив, в котором хранится количество операндов у оператора
};
#endif