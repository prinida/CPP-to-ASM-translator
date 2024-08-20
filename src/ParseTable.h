#ifndef PARSE_TABLE_H
#define PARSE_TABLE_H

#include "ParseTableElement.h"

#include <map>
#include <string>

// parse table class (for syntax analysis)
class ParseTable
{
public:
    ParseTable(std::string parseTableFileName); // reading a parse table from a file and writing it to an associative array

    std::map<unsigned int, ParseTableElement>& getParseTable() { return m_parseTable; };

private:
    std::map<unsigned int, ParseTableElement> m_parseTable; // associative array for pairs "id - parse table element(terminals, jump, accept, stack, error)"
};

#endif
