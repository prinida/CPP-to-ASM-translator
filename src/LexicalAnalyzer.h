#ifndef LEXICAL_ANALYZER_H
#define LEXICAL_ANALYZER_H

#include "StaticTable.h"
#include "Table.h"
#include "TokenTable.h"

#include <fstream>
#include <string>

// класс лексического анализа
class LexicalAnalyzer
{
public:
    LexicalAnalyzer(StaticTable<char>& _alphabet,
        StaticTable<std::string>& _keyWords,
        StaticTable<std::string>& _operators,
        StaticTable<std::string>& _separators,
        Table<std::string>& _identifiers,
        Table<std::string>& _literals,
        TokenTable& _tokenTable,
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

    Table<std::string>& identifiers; // статическая таблица идентификаторов
    Table<std::string>& literals; // статическая таблица литеральных констант

    TokenTable& tokenTable; // таблица токенов

    std::ifstream sourceFile; // файл исходной программы
    std::ofstream errors; // файл ошибок
};

#endif
