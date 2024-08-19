#ifndef PARSE_TABLE_H
#define PARSE_TABLE_H

#include "ParseTableElement.h"

#include <map>
#include <string>

// класс таблицы разбора
class ParseTable
{
public:
    ParseTable(std::string parseTableFileName); // конструктор для считывания файла таблицы разбора

    std::map<unsigned int, ParseTableElement>& getParseTable() { return m_parseTable; }; // получить ссылку на таблицу разбора

private:
    std::map<unsigned int, ParseTableElement> m_parseTable; // таблица разбора
};

#endif
