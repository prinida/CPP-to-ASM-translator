#ifndef TEMPLATE_STATIC_TABLE_H
#define TEMPLATE_STATIC_TABLE_H

// the abstract template class of static table
template<class TValue>
class TemplateStaticTable
{
public:
    virtual bool contains(TValue value) = 0; // does the static table contain an element 
};

#endif
