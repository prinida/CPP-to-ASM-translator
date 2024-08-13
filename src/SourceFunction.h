#ifndef SOURCE_FUNCTION_H
#define SOURCE_FUNCTION_H

#include "StaticTable.h"
#include "Table.h"
#include "TokenTable.h"

void menu(StaticTable<char>& _alphabet,
    StaticTable<std::string>& _keyWords,
    StaticTable<std::string>& _operators,
    StaticTable<std::string>& _separators,
    Table<std::string>& _identifiers,
    Table<std::string>& _literals,
    TokenTable& _tokenTable);

#endif
