#ifndef TEMPLATE_STATIC_TABLE_H
#define TEMPLATE_STATIC_TABLE_H

// aбстрактный шаблонный класс статической таблицы
template<class TValue>
class TemplateStaticTable
{
public:
    virtual bool contains(TValue value) = 0; // содержит ли статическая таблица элемент
};

#endif
