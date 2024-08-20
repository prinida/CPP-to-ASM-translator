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

// static table template class inherited from static table abstract template class
template<class TValue>
class StaticTable : TemplateStaticTable<TValue>
{
public:
    StaticTable(std::string fileName); // reading from static table file
    bool contains(TValue value) override; // does the static table contain an element 

private:
    std::vector<TValue> m_staticTable; // static table stored in sorted form
};

template<class TValue>
StaticTable<TValue>::StaticTable(std::string fileName)
{
    std::ifstream fin;
    fin.open(fileName);

    // checking the static table file is opened
    if (!fin.is_open())
    {
        size_t num = fileName.find_last_of("\\");
        std::string name = fileName.substr(num + 1, fileName.size() - num);

        std::cout << "Failed to open file " << name << std::endl;
        system("pause");
        exit(0);
    }

    TValue el{};

    // reading elements from file
    while (fin >> el)
        m_staticTable.push_back(el);

    // sorting elements from table to have efficient search in static table
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

    // use binary search because static table is sorted
    return std::binary_search(m_staticTable.begin(), m_staticTable.end(), searchEl,
        [](const TValue& el1, const TValue& el2)
        {
            return el1 < el2;
        });
}

#endif
