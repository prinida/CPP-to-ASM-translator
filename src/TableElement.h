#ifndef TABLE_ELEMENT_H
#define TABLE_ELEMENT_H

// ����� �������� ����������� �������
template<class TValue>
class TableElement
{
public:
    TableElement() : amount(0) {};
    TableElement(TValue _value, int _amount = 0) : value(_value), amount(_amount) {};

    TValue value; // ��������
    int amount; // ����������
};

#endif
