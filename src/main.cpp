#include "DynamicTable.h"
#include "StaticTable.h"
#include "Token.h"
#include "Translator.h"

#include <string>

int main(int argc, char** argv)
{
    std::string executablePath = argv[0];
    size_t num = executablePath.find_last_of("\\");
    executablePath = executablePath.substr(0, num);

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
        executablePath + "\\res\\errors.txt",
        executablePath + "\\res\\priorities.txt",
        executablePath + "\\res\\parseTable.txt",
        executablePath + "\\res\\postfix.txt",
        executablePath + "\\res\\assembler.txt",
        executablePath + "\\res\\operatorsOperandsNumber.txt");

    translator.doTranslate();

    return 0;
}
