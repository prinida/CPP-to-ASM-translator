#ifndef TRANSLATOR_H
#define TRANSLATOR_H

#include "DynamicTable.h"
#include "Identifier.h"
#include "Literal.h"
#include "StaticTable.h"
#include "Token.h"

#include <string>

// класс трансл€тора
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

    void doTranslate(); // выполнить трансл€цию

    std::string getResultMessage() { return m_resultMsg; }; // получить сообщение с результатом работы трансл€тора

private:
    StaticTable<char>& m_alphabet; // статическа€ таблица алфавита €зыка
    StaticTable<std::string>& m_keyWords; // статическа€ таблица ключевых слов €зыка
    StaticTable<std::string>& m_operators; // статическа€ таблица операторов €зыка
    StaticTable<std::string>& m_separators; // статическа€ таблица разделителей €зыка

    DynamicTable<Identifier>& m_identifiers; // статическа€ таблица идентификаторов
    DynamicTable<Literal>& m_literals; // статическа€ таблица литеральных констант
    DynamicTable<Token>& m_tokenTable; // таблица токенов

    std::string m_programFileName; // им€ файла программы
    std::string m_errorsFileName; // им€ файла ошибок
    std::string m_prioritiesFileName; // им€ файла приоритетов операторов и ключевых слов
    std::string m_parseTableFileName; // им€ файла таблицы разбора
    std::string m_postfixFileName; // им€ файла постфиксной записи
    std::string m_asmCodeFileName; // им€ файла ассемблерного кода
    std::string m_operandsNumberFileName; // им€ файла, в котором хранитс€ количество операндов у оператора

    std::string m_resultMsg; // сообщение, содержащее результат работы трансл€тора
};

#endif
