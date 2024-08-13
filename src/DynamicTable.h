#ifndef DYNAMIC_TABLE_H
#define DYNAMIC_TABLE_H

#include "TTable.h"

#include <list>

// ��������� ����� ������������ �������
template<class TValue>
class DynamicTable : TTable<TValue>
{
public:
    bool contains(TValue _value) override; // �������� �� ������������ ������� �������
    void add(TValue _value) override; // �������� ������� � ������������ �������
    void remove(TValue _value) override; // ������� ������� �� ������������ �������
    TValue pop() override; //  ������� ������� �� ������ ������� (�� ������ ������)
    bool isTableEmpty(); // ��������� ������ �� ������ (�������)
    std::list<TValue>& getTable();

private:
    std::list<TValue> table; // ������������ �������
};

template<class TValue>
bool DynamicTable<TValue>::contains(TValue _value)
{
    bool exist = false;
    auto iterator = std::find(table.begin(), table.end(), _value);

    if (iterator != table.end())
        exist = true;

    return exist;
}

template<class TValue>
void DynamicTable<TValue>::add(TValue _value)
{
    table.push_back(_value);
}

template<class TValue>
void DynamicTable<TValue>::remove(TValue _value)
{
    auto iterator = std::find(table.begin(), table.end(), _value);

    if (iterator != table.end())
        table.erase(iterator);
}

template<class TValue>
TValue DynamicTable<TValue>::pop()
{
    if (!table.empty())
    {
        TValue element = table.front();
        table.pop_front();

        return element;
    }
    else
        return TValue();
}

template<class TValue>
bool DynamicTable<TValue>::isTableEmpty()
{
    return table.empty();
}

template<class TValue>
std::list<TValue>& DynamicTable<TValue>::getTable()
{
    return table;
}

#endif
