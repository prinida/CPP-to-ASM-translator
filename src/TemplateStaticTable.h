#ifndef TEMPLATE_STATIC_TABLE_H
#define TEMPLATE_STATIC_TABLE_H

// a���������� ��������� ����� ����������� �������
template<class TValue>
class TemplateStaticTable
{
public:
    virtual bool contains(TValue value) = 0; // �������� �� ����������� ������� �������
};

#endif
