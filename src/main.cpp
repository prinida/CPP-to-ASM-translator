#include "DynamicTable.h"
#include "Identifier.h"
#include "Literal.h"
#include "Literal.h"
#include "StaticTable.h"
#include "Token.h"
#include "Translator.h"

#include <cstdlib>
#include <filesystem>
#include <iostream>
#include <string>

int main(int argc, char** argv)
{
    // get path to folder which stores exe file
    std::string executablePath = argv[0];
    size_t num = executablePath.find_last_of("\\");
    executablePath = executablePath.substr(0, num);

    // create if not exists results directory to store assembler, postfix, errors files
    std::filesystem::path resultsDirectory(executablePath + "\\results");

    if (!std::filesystem::exists(resultsDirectory))
        std::filesystem::create_directory(resultsDirectory);

    // create and fill all needed static tables
    StaticTable<char> alphabet(executablePath + "\\res\\alphabet.txt");
    StaticTable<std::string> keyWords(executablePath + "\\res\\keyWords.txt");
    StaticTable<std::string> operators(executablePath + "\\res\\operators.txt");
    StaticTable<std::string> separators(executablePath + "\\res\\separators.txt");

    // only create all needed dynamic tables
    DynamicTable<Identifier> identifiers;
    DynamicTable<Literal> literals;
    DynamicTable<Token> tokenTable;

    // send all needed for translation tables to translator class
    Translator translator(
        alphabet,
        keyWords,
        operators,
        separators,
        identifiers,
        literals,
        tokenTable,
        executablePath + "\\res\\program.txt",
        resultsDirectory.string() + "\\errors.txt",
        executablePath + "\\res\\priorities.txt",
        executablePath + "\\res\\parseTable.txt",
        resultsDirectory.string() + "\\postfix.txt",
        resultsDirectory.string() + "\\assembler.txt",
        executablePath + "\\res\\operatorsOperandsNumber.txt");

    // translate source program written on subset of C++ language to assembler program
    translator.doTranslate();

    // print translation result (success or errors)
    std::cout << translator.getResultMessage() << std::endl;

    system("pause");

    return 0;
}
