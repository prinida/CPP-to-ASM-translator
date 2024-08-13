#ifndef TTABLE_H
#define TTABLE_H

#include "TStaticTable.h"

// абстрактный шаблонный класс динамической таблицы
template<class TValue>
class TTable : public TStaticTable<TValue>
{
public:
    virtual void add(TValue value) = 0; // добавить элемент в динамическую таблицу
    virtual void remove(TValue value) = 0; // удалить элемент из динамической таблицы
};

#endif
