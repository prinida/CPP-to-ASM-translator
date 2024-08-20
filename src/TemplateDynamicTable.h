#ifndef TEMPLATE_DYNAMIC_TABLE_H
#define TEMPLATE_DYNAMIC_TABLE_H

#include "TemplateStaticTable.h"

// the abstract template class of dynamic table inherited from the abstract template class of static table
template<class TValue>
class TemplateDynamicTable : public TemplateStaticTable<TValue>
{
public:
    virtual void add(TValue value) = 0; // add element to dynamic table
    virtual void remove(TValue value) = 0; // remove element from dynamic table
    virtual TValue pop() = 0; // pop element from the front of the table
};

#endif
