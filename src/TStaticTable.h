#ifndef TSTATIC_TABLE_H
#define TSTATIC_TABLE_H

// a���������� ��������� ����� ����������� �������
template<class TValue>
class TStaticTable
{
public:
    virtual bool contains(TValue value) = 0; // �������� �� ����������� ������� �������
};

#endif
