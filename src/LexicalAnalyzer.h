#ifndef LEXICAL_ANALYZER_H
#define LEXICAL_ANALYZER_H

#include "DynamicTable.h"
#include "Identifier.h"
#include "Literal.h"
#include "StaticTable.h"
#include "Token.h"

#include <iosfwd>
#include <string>

// class of lexical analysis
class LexicalAnalyzer
{
public:
    LexicalAnalyzer(StaticTable<char>& alphabet,
        StaticTable<std::string>& keyWords,
        StaticTable<std::string>& operators,
        StaticTable<std::string>& separators,
        DynamicTable<Identifier>& identifiers,
        DynamicTable<Literal>& literals,
        DynamicTable<Token>& tokenTable,
        std::string programFile,
        std::string errorsFile);
    void doLexicalAnalysis(); // the main function that starts the lexical analysis

    bool getResult() { return m_success; }

private:
    void errorHandling(std::string errorText); // handling with lexical errors
    void printErrorMessageInFile(std::string errorText); // formatted error output to errors file
    void checkCloseTag(char openTag, char closeTag, char currentChar, std::string errorMsg, int currentStringNumber); // checking closing for opened tags

    StaticTable<char>& m_alphabet; // reference to a static table with the language alphabet
    StaticTable<std::string>& m_keyWords; // reference to a static table with the language keywords
    StaticTable<std::string>& m_operators; // reference to a static table with the language operators
    StaticTable<std::string>& m_separators; // reference to a static table with the language separators

    DynamicTable<Identifier>& m_identifiers; // reference to the identifiers dynamic table
    DynamicTable<Literal>& m_literals; // reference to the literals dynamic table
    DynamicTable<Token>& m_tokenTable; // reference to the tokens dynamic table

    std::ifstream m_sourceFile; // the source program file
    std::ofstream m_errors; // the errors file

    bool m_success = true; // if the lexical analysis worked successfully
};

#endif
