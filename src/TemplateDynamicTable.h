#ifndef TEMPLATE_DYNAMIC_TABLE_H
#define TEMPLATE_DYNAMIC_TABLE_H

#include "TemplateStaticTable.h"

// абстрактный шаблонный класс динамической таблицы
template<class TValue>
class TemplateDynamicTable : public TemplateStaticTable<TValue>
{
public:
    virtual void add(TValue value) = 0; // добавить элемент в динамическую таблицу
    virtual void remove(TValue value) = 0; // удалить элемент из динамической таблицы
    virtual TValue pop() = 0; //  извлечь элемент из начала таблицы (из начала списка)
};

#endif
