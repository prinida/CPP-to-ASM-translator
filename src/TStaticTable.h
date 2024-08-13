#ifndef TSTATIC_TABLE_H
#define TSTATIC_TABLE_H

// aбстрактный шаблонный класс статической таблицы
template<class TValue>
class TStaticTable
{
public:
    virtual bool contains(TValue value) = 0; // содержит ли статическая таблица элемент
};

#endif
