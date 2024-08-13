#ifndef STATIC_TABLE_H
#define STATIC_TABLE_H

#include "TStaticTable.h"

#include <algorithm>
#include <fstream>
#include <string>
#include <vector>

// шаблонный класс статической таблицы
template<class TValue>
class StaticTable : TStaticTable<TValue>
{
public:
    StaticTable(std::string fileName); // конструктор для считывания из файла статической таблицы
    bool contains(TValue _value) override; // содержит ли статическая таблица данный элемент
    int getIndex(TValue _value); // получить индекс данного элемента в статической таблице
    std::vector<TValue>& getStaticTable();

private:
    std::vector<TValue> staticTable; // статическая таблица, хранится в отсортированном виде
};

template<class TValue>
StaticTable<TValue>::StaticTable(std::string fileName)
{
    std::ifstream fin;
    fin.open(fileName);

    TValue el;

    while (fin >> el)
        staticTable.push_back(el);

    std::sort(staticTable.begin(), staticTable.end(),
        [](const TValue& el1, const TValue& el2)
        {
            return el1 < el2;
        });

    fin.close();
}

template<class TValue>
bool StaticTable<TValue>::contains(TValue _value)
{
    TValue searchEl(_value);

    return std::binary_search(staticTable.begin(), staticTable.end(), searchEl,
        [](const TValue& el1, const TValue& el2)
        {
            return el1 < el2;
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

        if (_value == staticTable[mid])
            return mid;

        if (_value > staticTable[mid])
            low = mid + 1;

        if (_value < staticTable[mid])
            high = mid - 1;
    }

    return -1;
}

template<class TValue>
std::vector<TValue>& StaticTable<TValue>::getStaticTable()
{
    return staticTable;
}

#endif
