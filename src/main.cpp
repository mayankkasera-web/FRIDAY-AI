// FRIDAY AI — Personal AI Assistant
// Application entry point

#include "friday/commands.h"

#include <iostream>
#include <string>

int main()
{
    // Load configuration before anything else
    friday::loadConfig("config/config.txt");

    friday::showGreeting();

    std::string input;
    bool running = true;

    while (running)
    {
        std::cout << friday::getPromptSymbol() << " ";
        std::getline(std::cin, input);
        running = friday::processCommand(input);
    }

    return 0;
}