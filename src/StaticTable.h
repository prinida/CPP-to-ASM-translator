#ifndef STATIC_TABLE_H
#define STATIC_TABLE_H

#include "TemplateStaticTable.h"

#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iosfwd>
#include <iostream>
#include <string>
#include <vector>

// шаблонный класс статической таблицы
template<class TValue>
class StaticTable : TemplateStaticTable<TValue>
{
public:
    StaticTable(std::string fileName); // конструктор для считывания из файла статической таблицы
    bool contains(TValue value) override; // содержит ли статическая таблица данный элемент

private:
    std::vector<TValue> m_staticTable; // статическая таблица, хранится в отсортированном виде
};

template<class TValue>
StaticTable<TValue>::StaticTable(std::string fileName)
{
    std::ifstream fin;
    fin.open(fileName);

    if (!fin.is_open())
    {
        size_t num = fileName.find_last_of("\\");
        std::string name = fileName.substr(num + 1, fileName.size() - num);

        std::cout << "Failed to open file " << name << std::endl;
        system("pause");
        exit(0);
    }

    TValue el{};

    while (fin >> el)
        m_staticTable.push_back(el);

    std::sort(m_staticTable.begin(), m_staticTable.end(),
        [](const TValue& el1, const TValue& el2)
        {
            return el1 < el2;
        });

    fin.close();
}

template<class TValue>
bool StaticTable<TValue>::contains(TValue value)
{
    TValue searchEl(value);

    return std::binary_search(m_staticTable.begin(), m_staticTable.end(), searchEl,
        [](const TValue& el1, const TValue& el2)
        {
            return el1 < el2;
        });
}

#endif
