// FRIDAY AI — Command declarations
#pragma once

#include <string>

namespace friday
{

    void loadConfig(const std::string &filepath);
    void showGreeting();
    void showHelp();
    void showAbout();
    void showStatus();
    void showTime();

    void handleNoteSave(const std::string &text);
    void handleNoteList();
    void handleNoteClear();

    bool processCommand(const std::string &input);
    std::string getPromptSymbol();

} // namespace friday