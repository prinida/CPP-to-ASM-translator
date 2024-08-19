#ifndef PARSER_H
#define PARSER_H

#include "DynamicTable.h"
#include "ParseTableElement.h"
#include "Token.h"

#include <fstream>
#include <iosfwd>
#include <map>
#include <string>
#include <vector>

// класс синтаксического анализатора (парсера)
class Parser
{
public:
    Parser(DynamicTable<Token>& tokenTable,
        std::map<unsigned int, ParseTableElement>& parseTable,
        std::string errorsFile,
        std::string prioritiesFile,
        std::string postfixFile);
    void doParse(); // выполнить синтаксический анализ

    std::vector<std::string>& getPostfix() { return m_postfix; } // получить ссылку на массив с постфиксной записью
    bool getResult() { return m_success; } // получить результат работы синтаксического анализатора (есть ошибки или нет)
    std::vector<std::string>& getLabels() { return m_labels; }; // получить ссылку на массив меток (для генерации ассемблерного кода)

private:
    void makePostfix(); // сделать постфиксную запись по инфексной 
    void errorHandling(std::string errorText, std::vector<std::string> possibleFixes); // обработка ошибки
    void printErrorMessageInFile(std::string errorText, std::vector<std::string> possibleFixes); // форматированный вывод ошибок в файл ошибок

    DynamicTable<Token>& m_tokenTable; // таблица токенов
    std::map<unsigned int, ParseTableElement>& m_parseTable; // таблица разбора

    std::ofstream m_errors; // файл ошибок
    std::ofstream m_postfixFile; // файл постфиксной записи

    std::map<std::string, int> m_priorities; // ассоциативный массив приоритетов операторов и ключевых слов
    std::vector<std::string> m_infix; // инфиксная запись
    std::vector<std::string> m_infixValue; // инфикс, содержащий значения токенов
    std::vector<std::string> m_postfix; // постфиксная запись
    std::vector<std::string> m_labels; // массив меток (для генерации ассемблерного кода)

    bool m_success = true; // успешен ли синтаксический анализ
};

#endif