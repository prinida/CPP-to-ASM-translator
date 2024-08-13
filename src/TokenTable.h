#ifndef TOKEN_TABLE_H
#define TOKEN_TABLE_H

#include "Token.h"
#include "Enums.h"

#include <list>

// класс таблицы токенов
class TokenTable
{
public:
    void add(Token value); // добавить токен в таблицу
    void printTable(); // напечатать в консоль таблицу токенов
    std::string getTokenStringName(tokenNames name); // перевести enum в string
    Token popToken(); // извлечь токен из начала таблицы (из начала списка)

private:
    std::list<Token> table; // таблица токенов
};

#endif 
