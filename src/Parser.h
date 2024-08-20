#ifndef PARSER_H
#define PARSER_H

#include "DynamicTable.h"
#include "ParseTableElement.h"
#include "Token.h"

#include <fstream>
#include <iosfwd>
#include <map>
#include <string>
#include <vector>

// syntax analysis class(parser)
class Parser
{
public:
    Parser(DynamicTable<Token>& tokenTable,
        std::map<unsigned int, ParseTableElement>& parseTable,
        std::string errorsFile,
        std::string prioritiesFile,
        std::string postfixFile);
    void doParse(); // main function for perfoming syntax analysis

    std::vector<std::string>& getPostfix() { return m_postfix; }
    bool getResult() { return m_success; }
    std::vector<std::string>& getLabels() { return m_labels; };

private:
    void makePostfix(); // make postfix notation from infix
    void errorHandling(std::string errorText, std::vector<std::string> possibleFixes); // handling with syntax errors
    void printErrorMessageInFile(std::string errorText, std::vector<std::string> possibleFixes); // formatted error output to errors file

    DynamicTable<Token>& m_tokenTable; // reference to the tokens dynamic table
    std::map<unsigned int, ParseTableElement>& m_parseTable; // reference to the parse table

    std::ofstream m_errors; // the errors file
    std::ofstream m_postfixFile; // the postfix notation file

    std::map<std::string, int> m_priorities; // associative array for pairs "operator or keyword - priority"
    std::vector<std::string> m_infix; // infix notation
    std::vector<std::string> m_infixValue; // infix notation with token's values
    std::vector<std::string> m_postfix; // postfix notation
    std::vector<std::string> m_labels; // labels array for generating assembly code

    bool m_success = true; // if the parser worked successfully
};

#endif