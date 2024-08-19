#include "ParseTable.h"
#include "ParseTableElement.h"

#include <cstdlib>
#include <fstream>
#include <iosfwd>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

ParseTable::ParseTable(std::string parseTableFileName)
{
    std::ifstream parseTableFile(parseTableFileName);

    if (!parseTableFile.is_open())
    {
        size_t num = parseTableFileName.find_last_of("\\");
        std::string name = parseTableFileName.substr(num + 1, parseTableFileName.size() - num);

        std::cout << "Failed to open file " << name << std::endl;
        system("pause");
        exit(0);
    }

    ParseTableElement element;

    unsigned int id = 0;
    std::string terminal;
    std::vector<std::string> terminals;
    unsigned int jump;
    bool accept;
    bool stack;
    bool error;

    while (parseTableFile >> terminal)
    {
        id++;
        terminals.clear();

        while (true)
        {
            terminal.erase(terminal.find("'"), 1);
            terminal.erase(terminal.find("'"), 1);

            if (terminal.find(",") == std::string::npos)
            {
                terminals.push_back(terminal);
                break;
            }
            else if (terminal.size() == 1)
            {
                terminals.push_back(terminal);
                break;
            }

            terminal.erase(terminal.find(","), 1);
            terminals.push_back(terminal);

            parseTableFile >> terminal;
        }

        parseTableFile >> jump;
        parseTableFile >> accept;
        parseTableFile >> stack;
        parseTableFile >> error;

        element.setTerminals(terminals);
        element.setJump(jump);
        element.setAccept(accept);
        element.setStack(stack);
        element.setError(error);

        std::pair<unsigned int, ParseTableElement> pair(id, element);

        m_parseTable.insert(pair);
    }
}
