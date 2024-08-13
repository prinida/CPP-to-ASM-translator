#include "AssemblerGenerator.h"
#include "DynamicTable.h"
#include "LexicalAnalyzer.h"
#include "Parser.h"
#include "ParseTable.h"
#include "StaticTable.h"
#include "Token.h"
#include "Translator.h"

#include <string>
#include <vector>

Translator::Translator(StaticTable<char>& _alphabet,
    StaticTable<std::string>& _keyWords,
    StaticTable<std::string>& _operators,
    StaticTable<std::string>& _separators,
    DynamicTable<std::string>& _identifiers,
    DynamicTable<std::string>& _literals,
    DynamicTable<Token>& _tokenTable,
    std::string _programFileName,
    std::string _errorsFileName,
    std::string _prioritiesFileName,
    std::string _parseTableFileName,
    std::string _postfixFileName,
    std::string _asmCodeFileName,
    std::string _operandsNumberFileName) :
    alphabet(_alphabet),
    keyWords(_keyWords),
    operators(_operators),
    separators(_separators),
    identifiers(_identifiers),
    literals(_literals),
    tokenTable(_tokenTable),
    programFileName(_programFileName),
    errorsFileName(_errorsFileName),
    prioritiesFileName(_prioritiesFileName),
    parseTableFileName(_parseTableFileName),
    postfixFileName(_postfixFileName),
    asmCodeFileName(_asmCodeFileName),
    operandsNumberFileName(_operandsNumberFileName)
{
}

void Translator::doTranslate()
{
    LexicalAnalyzer lexer(alphabet, keyWords, operators, separators, identifiers, literals, tokenTable, programFileName, errorsFileName);
    lexer.doLexicalAnalysis();

    ParseTable parseTable(parseTableFileName);
    Parser parser(tokenTable, parseTable.getParseTable(), errorsFileName, prioritiesFileName, postfixFileName);
    parser.doParse();

    if (parser.getSyntaxResult())
    {
        std::vector<std::string>& postfix = parser.getPostfix();
        AssemblerGenerator generator(parser.getLabels(), postfix, identifiers, literals, asmCodeFileName, operandsNumberFileName);
        generator.generateAssemblerInitSection();
        generator.generateAssemblerDataSection();
        generator.generateAssemblerCodeSection();
    }
}
