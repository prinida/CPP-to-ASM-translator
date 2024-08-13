#ifndef PARSER_H
#define PARSER_H

#include "TokenTable.h"
#include "ParseTableElement.h"

#include <map>
#include <vector>
#include <fstream>

// класс синтаксического анализатора (парсера)
class Parser
{
public:
    Parser(TokenTable _tokenTable, 
        std::map<unsigned int, ParseTableElement>& _parseTable, 
        std::string _errorsFile, 
        std::string _prioritiesFile,
        std::string _postfixFile);
    void doParse(); // выполнить синтаксический анализ
    void makePostfix(); // сделать постфиксную запись по инфексной 
    void printErrorMessageInFile(std::string errorText, std::vector<std::string> possibleFixes); // форматированный вывод ошибок в файл ошибок
    std::vector<std::string>& getPostfix() { return postfix; } // получить ссылку на массив с постфиксной записью
    bool getSyntaxResult() { return success; } // получить результат работы синтаксического анализатора (есть ошибки или нет)
    std::vector<std::string>& getLabels() { return labels; }; // получить ссылку на массив меток (для генерации ассемблерного кода)

private:
    TokenTable tokenTable; // таблица токенов
    std::map<unsigned int, ParseTableElement>& parseTable; // таблица разбора

    std::ofstream errors; // файл ошибок
    std::ofstream postfixFile; // файл постфиксной записи

    std::map<std::string, int> priorities; // ассоциативный массив приоритетов операторов и ключевых слов
    std::vector<std::string> infix; // инфиксная запись
    std::vector<std::string> infixValue; // инфикс, содержащий значения токенов
    std::vector<std::string> postfix; // постфиксная запись
    std::vector<std::string> labels; // массив меток (для генерации ассемблерного кода)
     
    bool success = true; // успешен ли синтаксический анализ
};

#endif