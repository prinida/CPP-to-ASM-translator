#ifndef TRANSLATOR_H
#define TRANSLATOR_H

#include "DynamicTable.h"
#include "Identifier.h"
#include "Literal.h"
#include "StaticTable.h"
#include "Token.h"

#include <string>

// translator class - main class responsible for all phases of translation subset of CPP to Assembler
class Translator
{
public:
    Translator(StaticTable<char>& alphabet,
        StaticTable<std::string>& keyWords,
        StaticTable<std::string>& operators,
        StaticTable<std::string>& separators,
        DynamicTable<Identifier>& identifiers,
        DynamicTable<Literal>& literals,
        DynamicTable<Token>& tokenTable,
        std::string programFileName,
        std::string errorsFileName,
        std::string prioritiesFileName,
        std::string parseTableFileName,
        std::string postfixFileName,
        std::string asmCodeFileName,
        std::string operandsNumberFileName);

    void doTranslate(); // perform translation

    std::string getResultMessage() { return m_resultMsg; };

private:
    StaticTable<char>& m_alphabet; // reference to a static table with the language alphabet
    StaticTable<std::string>& m_keyWords; // reference to a static table with the language keywords
    StaticTable<std::string>& m_operators; // reference to a static table with the language operators
    StaticTable<std::string>& m_separators; // reference to a static table with the language separators

    DynamicTable<Identifier>& m_identifiers; // reference to the identifiers dynamic table
    DynamicTable<Literal>& m_literals; // reference to the literals dynamic table
    DynamicTable<Token>& m_tokenTable; // reference to the tokens dynamic table

    std::string m_programFileName; // source program file name
    std::string m_errorsFileName; // errors file name
    std::string m_prioritiesFileName; // operator and keyword priorities file name
    std::string m_parseTableFileName; // parse table file name
    std::string m_postfixFileName; // postfix notation file name
    std::string m_asmCodeFileName; // assembler program file name
    std::string m_operandsNumberFileName; // the name of the file that stores the number of operands for the operator

    std::string m_resultMsg; // a message containing the result of the translator's work
};

#endif
