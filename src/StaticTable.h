#ifndef STATIC_TABLE_H
#define STATIC_TABLE_H

#include "TemplateStaticTable.h"

#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

// ��������� ����� ����������� �������
template<class TValue>
class StaticTable : TemplateStaticTable<TValue>
{
public:
    StaticTable(std::string fileName); // ����������� ��� ���������� �� ����� ����������� �������
    bool contains(TValue _value) override; // �������� �� ����������� ������� ������ �������

private:
    std::vector<TValue> staticTable; // ����������� �������, �������� � ��������������� ����
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

#endif
