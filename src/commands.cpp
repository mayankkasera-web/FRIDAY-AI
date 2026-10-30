// FRIDAY AI — Command implementations

#include "friday/commands.h"
#include "friday/notes.h"
#include "friday/config.h"

#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>
#include <chrono>
#include <format>

namespace friday
{

    // --- Global Config Instance ---
    // (We'll improve this in a later phase with dependency injection)
    static Config g_config;

    // --- Local Helper ---

    std::string toLower(std::string text)
    {
        std::transform(text.begin(), text.end(), text.begin(),
                       [](unsigned char c)
                       { return std::tolower(c); });
        return text;
    }

    // --- Config Access ---

    void loadConfig(const std::string &filepath)
    {
        g_config.load(filepath);
    }

    // --- Command Implementations ---

    void showGreeting()
    {
        std::string name = g_config.get("assistant_name", "FRIDAY");
        std::string version = g_config.get("version", "0.1.0");
        std::string greeting = g_config.get("greeting", "Hello!");

        std::cout << "================================\n";
        std::cout << "  " << name << " AI v" << version << "\n";
        std::cout << "  Personal AI Assistant\n";
        std::cout << "================================\n\n";

        std::cout << greeting << "\n";
        std::cout << "Type 'help' for available commands.\n";
        std::cout << "Type 'exit' to shut down.\n\n";
    }

    void showHelp()
    {
        std::cout << "\n--- Available Commands ---\n";
        std::cout << "  help             Show this help message\n";
        std::cout << "  about            Show information about FRIDAY\n";
        std::cout << "  status           Show system status\n";
        std::cout << "  time             Show current date and time\n";
        std::cout << "  note save <text> Save a note\n";
        std::cout << "  note list        Show all saved notes\n";
        std::cout << "  note clear       Delete all notes\n";
        std::cout << "  exit             Shut down\n";
        std::cout << "  quit             Shut down\n";
        std::cout << "--------------------------\n\n";
    }

    void showAbout()
    {
        std::string name = g_config.get("assistant_name", "FRIDAY");
        std::string version = g_config.get("version", "0.1.0");

        std::cout << "\n--- About " << name << " ---\n";
        std::cout << "  " << name << " AI v" << version << "\n";
        std::cout << "  A personal AI assistant built with Modern C++23.\n";
        std::cout << "  Inspired by Iron Man's F.R.I.D.A.Y.\n";
        std::cout << "--------------------\n\n";
    }

    void showStatus()
    {
        std::string name = g_config.get("assistant_name", "FRIDAY");
        std::string version = g_config.get("version", "0.1.0");

        std::cout << "\n--- System Status ---\n";
        std::cout << "  Name:       " << name << "\n";
        std::cout << "  Version:    " << version << "\n";
        std::cout << "  Status:     Online\n";
        std::cout << "  AI Engine:  Not connected\n";
        std::cout << "  Voice:      Not available\n";
        std::cout << "  Notes:      Local file storage\n";
        std::cout << "---------------------\n\n";
    }

    void showTime()
    {
        auto now = std::chrono::system_clock::now();

        std::cout << "\n--- Current Date & Time ---\n";
        std::cout << std::format("  Date: {:%Y-%m-%d}\n", now);
        std::cout << std::format("  Time: {:%H:%M:%S}\n", now);
        std::cout << std::format("  Day:  {:%A}\n", now);
        std::cout << "---------------------------\n\n";
    }

    // --- Note Command Handlers ---

    void handleNoteSave(const std::string &text)
    {
        if (text.empty())
        {
            std::cout << "Please provide note text. Usage: note save <text>\n\n";
            return;
        }
        saveNote(text);
        std::cout << "Note saved successfully!\n\n";
    }

    void handleNoteList()
    {
        auto notes = loadNotes();

        if (notes.empty())
        {
            std::cout << "\nNo notes found. Use 'note save <text>' to create one.\n\n";
            return;
        }

        std::cout << "\n--- Your Notes (" << notes.size() << ") ---\n";
        for (size_t i = 0; i < notes.size(); ++i)
        {
            std::cout << "  " << (i + 1) << ". [" << notes[i].timestamp << "] "
                      << notes[i].text << "\n";
        }
        std::cout << "--------------------------------\n\n";
    }

    void handleNoteClear()
    {
        clearNotes();
        std::cout << "\nAll notes deleted.\n\n";
    }

    // --- Command Processor ---

    bool processCommand(const std::string &input)
    {
        std::string command = toLower(input);

        if (command == "exit" || command == "quit")
        {
            std::cout << "\nShutting down. Goodbye!\n";
            return false;
        }
        else if (command == "help")
        {
            showHelp();
        }
        else if (command == "about")
        {
            showAbout();
        }
        else if (command == "status")
        {
            showStatus();
        }
        else if (command == "time")
        {
            showTime();
        }
        else if (command.starts_with("note save "))
        {
            std::string noteText = input.substr(10);
            handleNoteSave(noteText);
        }
        else if (command == "note save")
        {
            handleNoteSave("");
        }
        else if (command == "note list")
        {
            handleNoteList();
        }
        else if (command == "note clear")
        {
            handleNoteClear();
        }
        else if (command.starts_with("note"))
        {
            std::cout << "Unknown note command. Try: note save, note list, note clear\n\n";
        }
        else if (command.empty())
        {
            // Do nothing
        }
        else
        {
            std::cout << "Unknown command: '" << input << "'\n";
            std::cout << "Type 'help' for available commands.\n\n";
        }

        return true;
    }

    std::string getPromptSymbol()
    {
        return g_config.get("prompt_symbol", "friday>");
    }

} // namespace friday