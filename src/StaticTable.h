#ifndef STATIC_TABLE_H
#define STATIC_TABLE_H

#include "TStaticTable.h"
#include "TableElement.h"

#include <algorithm>
#include <string>
#include <vector>
#include <iostream>

// шаблонный класс статической таблицы
template<class TValue>
class StaticTable : TStaticTable<TValue>
{
public:
    StaticTable(std::string fileName); // конструктор для считывания из файла статической таблицы
    bool contains(TValue _value) override; // содержит ли статическая таблица данный элемент
    int getIndex(TValue _value); // получить индекс данного элемента в статической таблице
    void incrementElementAmount(int index); // инкрементировать значение количества элемента по индексу
    void printTable(std::string tableName, bool withAmount); // напечатать статическую таблицу в консоль
    void printContains(TValue _value); // напечать в консоль содержиться ли данный элемент в статической таблице
    std::vector<TableElement<TValue>> getStaticTable();

private:
    std::vector<TableElement<TValue>> staticTable; // статическая таблица
};

template<class TValue>
StaticTable<TValue>::StaticTable(std::string fileName)
{
    std::ifstream fin;
    fin.open(fileName);

    TableElement<TValue> el;

    while (fin >> el.value)
        staticTable.push_back(el);

    std::sort(staticTable.begin(), staticTable.end(),
        [](const TableElement<TValue>& el1, const TableElement<TValue>& el2)
        {
            return el1.value < el2.value;
        });

    fin.close();
}

template<class TValue>
bool StaticTable<TValue>::contains(TValue _value)
{
    TableElement<TValue> searchEl(_value);

    return std::binary_search(staticTable.begin(), staticTable.end(), searchEl,
        [](const TableElement<TValue>& el1, const TableElement<TValue>& el2)
        {
            return el1.value < el2.value;
        });
}

template<class TValue>
int StaticTable<TValue>::getIndex(TValue _value)
{
    int low = 0;
    int high = staticTable.size() - 1;

    while (low <= high)
    {
        int mid = low + (high - low) / 2;

        if (_value == staticTable[mid].value)
            return mid;

        if (_value > staticTable[mid].value)
            low = mid + 1;

        if (_value < staticTable[mid].value)
            high = mid - 1;
    }

    return -1;
}

template<class TValue>
void StaticTable<TValue>::incrementElementAmount(int index)
{
    staticTable[index].amount++;
}

template<class TValue>
void StaticTable<TValue>::printTable(std::string tableName, bool withAmount)
{
    std::cout << tableName << ":\n";
    int count = 0;

    for (auto el : staticTable)
    {
        if (withAmount)
            std::cout << "  " << el.value << ": " << el.amount << '\n';
        else
        {
            if (count == staticTable.size() - 1)
                std::cout << el.value << '\n';
            else
                std::cout << el.value << ", ";
        }

        count++;
    }
}

template<class TValue>
void StaticTable<TValue>::printContains(TValue _value)
{
    contains(_value) ? std::cout << "yes" << '\n' : std::cout << "no" << '\n';
}

template<class TValue>
std::vector<TableElement<TValue>> StaticTable<TValue>::getStaticTable()
{
    return staticTable;
}

#endif
