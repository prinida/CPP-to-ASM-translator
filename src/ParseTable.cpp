#include "ParseTable.h"

#include <fstream>
#include <iostream>

ParseTable::ParseTable(std::string parseTableFileName)
{
    std::ifstream parseTableFile(parseTableFileName);

    if (!parseTableFile.is_open())
        std::cout << "Unable to open parse table file!" << std::endl;
    else
    {
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

            parseTable.insert(pair);
        }
    }
}
