#ifndef TABLE_H
#define TABLE_H

#include "TTable.h"

#include <string>
#include <list>
#include <iostream>

// ��������� ����� ������������ �������
template<class TValue>
class Table : TTable<TValue>
{
public:
    bool contains(TValue _value) override; // �������� �� ������������ ������� �������
    void add(TValue _value) override; // �������� ������� � ������������ �������
    void remove(TValue _value) override; // ������� ������� �� ������������ �������
    void printTable(std::string tableName); // ��������� ������������ ������� � �������
    void printContains(TValue _value); // ��������� � ������� �������� �� ������������ ������� �������
    std::list<TValue>& getTable();

private:
    std::list<TValue> table; // ������������ �������
};

template<class TValue>
bool Table<TValue>::contains(TValue _value)
{
    bool exist = false;
    auto iterator = std::find(table.begin(), table.end(), _value);

    if (iterator != table.end())
        exist = true;

    return exist;
}

template<class TValue>
void Table<TValue>::add(TValue _value)
{
    table.push_back(_value);
}

template<class TValue>
void Table<TValue>::remove(TValue _value)
{
    auto iterator = std::find(table.begin(), table.end(), _value);

    if (iterator != table.end())
        table.erase(iterator);
}

template<class TValue>
void Table<TValue>::printTable(std::string tableName)
{
    std::cout << tableName << ":\n";

    for (auto el : table)
        std::cout << "  " << el << '\n';
}

template<class TValue>
void Table<TValue>::printContains(TValue _value)
{
    contains(_value) ? std::cout << "yes" << '\n' : std::cout << "no" << '\n';
}

template<class TValue>
inline std::list<TValue>& Table<TValue>::getTable()
{
    return table;
}


#endif
