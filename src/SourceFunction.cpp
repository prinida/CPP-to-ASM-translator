#include "SourceFunction.h"

#include <iostream>

void menu(StaticTable<char>& alphabet,
    StaticTable<std::string>& keyWords,
    StaticTable<std::string>& operators,
    StaticTable<std::string>& separators,
    Table<std::string>& identifiers,
    Table<std::string>& literals,
    TokenTable& tokenTable)
{
    bool flag = false;

    do
    {
        std::cout << "-------------------------------------------------------------------\n";
        std::cout << "Select the desired menu item below: \n\n";
        std::cout << "Show alphabet table.                                            - 0 \n";
        std::cout << "Does the element exist in the permanent alphabet table?         - 1 \n";
        std::cout << "Show key word table.                                            - 2 \n";
        std::cout << "Does the element exist in the permanent key word table?         - 3 \n";
        std::cout << "Show operators table.                                           - 4 \n";
        std::cout << "Does the element exist in the permanent operators table?        - 5 \n";
        std::cout << "Show separators table.                                          - 6 \n";
        std::cout << "Does the element exist in the permanent separators table?       - 7 \n";
        std::cout << "Show identifiers table.                                         - 8 \n";
        std::cout << "Add element in identifiers table.                               - 9 \n";
        std::cout << "Remove element from identifiers table.                          - 10 \n";
        std::cout << "Does the element exist in the identifiers table?                - 11 \n";
        std::cout << "Show literals table.                                            - 12 \n";
        std::cout << "Add element in literals table.                                  - 13 \n";
        std::cout << "Remove element from literals table.                             - 14 \n";
        std::cout << "Does the element exist in the literals table?                   - 15 \n";
        std::cout << "Show table of tokens.                                           - 16 \n";
        std::cout << "End the program                                                 - 17 \n\n";
        std::cout << "-------------------------------------------------------------------\n\n";
        std::cout << ">> ";

        int num;
        char valueSymbol;
        std::string valueString;
        std::cin >> num;

        switch (num)
        {
        case 0:
            alphabet.printTable("Alphabet table", false);
            break;
        case 1:
            std::cout << "Input symbol value: ";
            std::cin >> valueSymbol;
            alphabet.printContains(valueSymbol);
            break;
        case 2:
            keyWords.printTable("Key words table", true);
            break;
        case 3:
            std::cout << "Input symbol value: ";
            std::cin >> valueString;
            keyWords.printContains(valueString);
            break;
        case 4:
            operators.printTable("Operators table", true);
            break;
        case 5:
            std::cout << "Input symbol value: ";
            std::cin >> valueString;
            operators.printContains(valueString);
            break;
        case 6:
            separators.printTable("Separators table", true);
            break;
        case 7:
            std::cout << "Input symbol value: ";
            std::cin >> valueString;
            separators.printContains(valueString);
            break;
        case 8:
            identifiers.printTable("Identifiers table");
            break;
        case 9:
            std::cout << "Input symbol value: ";
            std::cin >> valueString;
            identifiers.add(valueString);
            break;
        case 10:
            std::cout << "Input symbol value: ";
            std::cin >> valueString;
            identifiers.remove(valueString);
            break;
        case 11:
            std::cout << "Input symbol value: ";
            std::cin >> valueString;
            identifiers.printContains(valueString);
            break;
        case 12:
            literals.printTable("Literals table");
            break;
        case 13:
            std::cout << "Input symbol value: ";
            std::cin >> valueString;
            literals.add(valueString);
            break;
        case 14:
            std::cout << "Input symbol value: ";
            std::cin >> valueString;
            literals.remove(valueString);
            break;
        case 15:
            std::cout << "Input symbol value: ";
            std::cin >> valueString;
            literals.printContains(valueString);
            break;
        case 16:
            tokenTable.printTable();
            break;
        case 17:
            flag = true;
            break;
        default:
            std::cout << "Incorrect input\n";
        }

    } while (!flag);
}