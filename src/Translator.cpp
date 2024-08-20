#include "AssemblerGenerator.h"
#include "DynamicTable.h"
#include "Identifier.h"
#include "LexicalAnalyzer.h"
#include "Literal.h"
#include "Parser.h"
#include "ParseTable.h"
#include "StaticTable.h"
#include "Token.h"
#include "Translator.h"

#include <filesystem>
#include <string>
#include <vector>

Translator::Translator(StaticTable<char>& alphabet,
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
    std::string operandsNumberFileName) :
    m_alphabet(alphabet),
    m_keyWords(keyWords),
    m_operators(operators),
    m_separators(separators),
    m_identifiers(identifiers),
    m_literals(literals),
    m_tokenTable(tokenTable),
    m_programFileName(programFileName),
    m_errorsFileName(errorsFileName),
    m_prioritiesFileName(prioritiesFileName),
    m_parseTableFileName(parseTableFileName),
    m_postfixFileName(postfixFileName),
    m_asmCodeFileName(asmCodeFileName),
    m_operandsNumberFileName(operandsNumberFileName) {}

void Translator::doTranslate()
{
    // perform lexical analysis, fill errors file in errors case
    LexicalAnalyzer lexer(m_alphabet, m_keyWords, m_operators, m_separators, m_identifiers, m_literals, m_tokenTable, m_programFileName, m_errorsFileName);
    lexer.doLexicalAnalysis();

    // get parse table
    ParseTable parseTable(m_parseTableFileName);

    // perform syntactic analysis, fill postfix file in success case, else fill errors file
    Parser parser(m_tokenTable, parseTable.getParseTable(), m_errorsFileName, m_prioritiesFileName, m_postfixFileName);
    parser.doParse();

    // if lexer and parser were worked successfully generate assembler file and set successful message else set errors message
    if (parser.getResult() && lexer.getResult())
    {
        std::vector<std::string>& postfix = parser.getPostfix();
        AssemblerGenerator generator(parser.getLabels(), postfix, m_identifiers, m_literals, m_asmCodeFileName, m_operandsNumberFileName);
        generator.generateAssembler();

        // remove not needed files
        if (std::filesystem::exists(m_errorsFileName))
            std::filesystem::remove(m_errorsFileName);

        m_resultMsg = "Translator has been finished successfully.\nYou can observe assembler code and postfix notation in the results folder in the assembler.txt and postfix.txt files respectively.\n\n";
    }
    else
    {
        // remove not needed files
        if (std::filesystem::exists(m_postfixFileName))
            std::filesystem::remove(m_postfixFileName);
        if (std::filesystem::exists(m_asmCodeFileName))
            std::filesystem::remove(m_asmCodeFileName);

        m_resultMsg = "There were some lexical or syntax errors in the input program!\nDetailed information is contained in the results folder in the errors.txt file.\n\n";
    }
}