#ifndef TEMPLATE_DYNAMIC_TABLE_H
#define TEMPLATE_DYNAMIC_TABLE_H

#include "TemplateStaticTable.h"

// ����������� ��������� ����� ������������ �������
template<class TValue>
class TemplateDynamicTable : public TemplateStaticTable<TValue>
{
public:
    virtual void add(TValue value) = 0; // �������� ������� � ������������ �������
    virtual void remove(TValue value) = 0; // ������� ������� �� ������������ �������
    virtual TValue pop() = 0; //  ������� ������� �� ������ ������� (�� ������ ������)
};

#endif
