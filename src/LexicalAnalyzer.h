#ifndef LEXICAL_ANALYZER_H
#define LEXICAL_ANALYZER_H

#include "DynamicTable.h"
#include "StaticTable.h"

#include "Token.h"
#include <string>

// класс лексического анализа
class LexicalAnalyzer
{
public:
    LexicalAnalyzer(StaticTable<char>& _alphabet,
        StaticTable<std::string>& _keyWords,
        StaticTable<std::string>& _operators,
        StaticTable<std::string>& _separators,
        DynamicTable<std::string>& _identifiers,
        DynamicTable<std::string>& _literals,
        DynamicTable<Token>& _tokenTable,
        std::string programFile,
        std::string errorsFile);
    void doLexicalAnalysis(); // функция, при вызове который осуществляется лексический анализ
    void printErrorMessageInFile(std::string errorText); // форматированный вывод ошибок в файл ошибок

private:
    void checkCloseTag(char openTag, char closeTag, char currentChar, std::string errorMsg, int currentStringNumber); // функция, нужная для проверки на закрытие всех открытых тегов

    StaticTable<char>& alphabet; // статическая таблица алфавита языка
    StaticTable<std::string>& keyWords; // статическая таблица ключевых слов языка
    StaticTable<std::string>& operators; // статическая таблица операторов языка
    StaticTable<std::string>& separators; // статическая таблица разделителей языка

    DynamicTable<std::string>& identifiers; // статическая таблица идентификаторов
    DynamicTable<std::string>& literals; // статическая таблица литеральных констант

    DynamicTable<Token>& tokenTable; // таблица токенов

    std::ifstream sourceFile; // файл исходной программы
    std::ofstream errors; // файл ошибок
};

#endif
