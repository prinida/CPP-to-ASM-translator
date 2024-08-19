#ifndef DYNAMIC_TABLE_H
#define DYNAMIC_TABLE_H

#include "TemplateDynamicTable.h"

#include <list>

// dynamic table template class inherited from dynamic table abstract template class
template<class TValue>
class DynamicTable : TemplateDynamicTable<TValue>
{
public:
    bool contains(TValue value) override; // does the dynamic table contain an element 
    void add(TValue value) override; // add element to dynamic table
    void remove(TValue value) override; // remove element from dynamic table
    TValue pop() override; // pop element from the front of the table(from the front of the list)
    bool isTableEmpty(); // checking if table is empty

    std::list<TValue>& getTable() { return m_table; };

private:
    std::list<TValue> m_table; // dynamic table(list)
};

template<class TValue>
bool DynamicTable<TValue>::contains(TValue value)
{
    bool exist = false;
    auto iterator = std::find(m_table.begin(), m_table.end(), value);

    if (iterator != m_table.end())
        exist = true;

    return exist;
}

template<class TValue>
void DynamicTable<TValue>::add(TValue value)
{
    m_table.push_back(value);
}

template<class TValue>
void DynamicTable<TValue>::remove(TValue value)
{
    auto iterator = std::find(m_table.begin(), m_table.end(), value);

    if (iterator != m_table.end())
        m_table.erase(iterator);
}

template<class TValue>
TValue DynamicTable<TValue>::pop()
{
    if (!m_table.empty())
    {
        TValue element = m_table.front();
        m_table.pop_front();

        return element;
    }
    else
        return TValue();
}

template<class TValue>
bool DynamicTable<TValue>::isTableEmpty()
{
    return m_table.empty();
}

#endif
