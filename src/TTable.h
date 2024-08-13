#ifndef TTABLE_H
#define TTABLE_H

#include "TStaticTable.h"

// ����������� ��������� ����� ������������ �������
template<class TValue>
class TTable : public TStaticTable<TValue>
{
public:
    virtual void add(TValue value) = 0; // �������� ������� � ������������ �������
    virtual void remove(TValue value) = 0; // ������� ������� �� ������������ �������
};

#endif
