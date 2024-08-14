#include "DynamicTable.h"
#include "StaticTable.h"
#include "Token.h"
#include "Translator.h"

#include <cstdlib>
#include <filesystem>
#include <iostream>
#include <string>

int main(int argc, char** argv)
{
    std::string executablePath = argv[0];
    size_t num = executablePath.find_last_of("\\");
    executablePath = executablePath.substr(0, num);

    std::filesystem::path resultsDirectory(executablePath + "\\results");

    if (!std::filesystem::exists(resultsDirectory))
        std::filesystem::create_directory(resultsDirectory);

    StaticTable<char> alphabet(executablePath + "\\res\\alphabet.txt");
    StaticTable<std::string> keyWords(executablePath + "\\res\\keyWords.txt");
    StaticTable<std::string> operators(executablePath + "\\res\\operators.txt");
    StaticTable<std::string> separators(executablePath + "\\res\\separators.txt");

    DynamicTable<std::string> identifiers;
    DynamicTable<std::string> literals;
    DynamicTable<Token> tokenTable;

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

    translator.doTranslate();

    std::cout << translator.getResultMessage() << std::endl;

    system("pause");

    return 0;
}
