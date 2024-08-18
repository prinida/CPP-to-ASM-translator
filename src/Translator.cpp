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

Translator::Translator(StaticTable<char>& _alphabet,
    StaticTable<std::string>& _keyWords,
    StaticTable<std::string>& _operators,
    StaticTable<std::string>& _separators,
    DynamicTable<Identifier>& _identifiers,
    DynamicTable<Literal>& _literals,
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

    if (parser.getResult() && lexer.getResult())
    {
        std::vector<std::string>& postfix = parser.getPostfix();
        AssemblerGenerator generator(parser.getLabels(), postfix, identifiers, literals, asmCodeFileName, operandsNumberFileName);
        generator.generateAssemblerInitSection();
        generator.generateAssemblerDataSection();
        generator.generateAssemblerCodeSection();

        if (std::filesystem::exists(errorsFileName))
            std::filesystem::remove(errorsFileName);

        resultMsg = "Translator has been finished successfully.\nYou can observe assembler code and postfix notation in the results folder in the assembler.txt and postfix.txt files respectively.\n\n";
    }
    else
    {
        if (std::filesystem::exists(postfixFileName))
            std::filesystem::remove(postfixFileName);
        if (std::filesystem::exists(asmCodeFileName))
            std::filesystem::remove(asmCodeFileName);

        resultMsg = "There were some lexical or syntax errors in the input program!\nDetailed information is contained in the results folder in the errors.txt file.\n\n";
    }
}

std::string Translator::getResultMessage()
{
    return resultMsg;
}
