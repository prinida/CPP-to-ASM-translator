#ifndef TRANSLATOR_H
#define TRANSLATOR_H

#include "DynamicTable.h"
#include "Identifier.h"
#include "Literal.h"
#include "StaticTable.h"

#include <string>

// класс трансл€тора
class Translator
{
public:
    Translator(StaticTable<char>& _alphabet,
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
        std::string _operandsNumberFileName);

    void doTranslate(); // выполнить трансл€цию
    std::string getResultMessage(); // получить сообщение с результатом работы трансл€тора

private:
    StaticTable<char>& alphabet; // статическа€ таблица алфавита €зыка
    StaticTable<std::string>& keyWords; // статическа€ таблица ключевых слов €зыка
    StaticTable<std::string>& operators; // статическа€ таблица операторов €зыка
    StaticTable<std::string>& separators; // статическа€ таблица разделителей €зыка

    DynamicTable<Identifier>& identifiers; // статическа€ таблица идентификаторов
    DynamicTable<Literal>& literals; // статическа€ таблица литеральных констант
    DynamicTable<Token>& tokenTable; // таблица токенов

    std::string programFileName; // им€ файла программы
    std::string errorsFileName; // им€ файла ошибок
    std::string prioritiesFileName; // им€ файла приоритетов операторов и ключевых слов
    std::string parseTableFileName; // им€ файла таблицы разбора
    std::string postfixFileName; // им€ файла постфиксной записи
    std::string asmCodeFileName; // им€ файла ассемблерного кода
    std::string operandsNumberFileName; // им€ файла, в котором хранитс€ количество операндов у оператора

    std::string resultMsg; // сообщение, содержащее результат работы трансл€тора
};

#endif
