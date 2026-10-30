// FRIDAY AI — Notes module implementation

#include "friday/notes.h"

#include <fstream>
#include <filesystem>
#include <chrono>
#include <format>
#include <iostream>

namespace friday
{

    namespace fs = std::filesystem;

    // --- Constants ---
    const std::string DATA_DIR = "data";
    const std::string NOTES_FILE = "data/notes.txt";

    // --- Internal Helper ---

    void ensureDataDirectory()
    {
        if (!fs::exists(DATA_DIR))
        {
            fs::create_directories(DATA_DIR);
        }
    }

    // --- Public Functions ---

    void saveNote(const std::string &text)
    {
        ensureDataDirectory();

        auto now = std::chrono::system_clock::now();
        std::string timestamp = std::format("{:%Y-%m-%d %H:%M:%S}", now);

        std::ofstream file(NOTES_FILE, std::ios::app);
        if (file.is_open())
        {
            file << "[" << timestamp << "] " << text << "\n";
        }
        else
        {
            std::cout << "Error: Could not open notes file for writing.\n";
        }
    }

    std::vector<Note> loadNotes()
    {
        std::vector<Note> notes;

        if (!fs::exists(NOTES_FILE))
        {
            return notes;
        }

        std::ifstream file(NOTES_FILE);
        if (!file.is_open())
        {
            std::cout << "Error: Could not open notes file for reading.\n";
            return notes;
        }

        std::string line;
        while (std::getline(file, line))
        {
            // Expected format: [2025-07-12 14:30:45] Note text here
            //                  0123456789012345678901
            if (line.size() >= 22 && line[0] == '[' && line[20] == ']')
            {
                Note note;
                note.timestamp = line.substr(1, 19);
                note.text = line.substr(22);
                notes.push_back(note);
            }
        }

        return notes;
    }

    void clearNotes()
    {
        if (fs::exists(NOTES_FILE))
        {
            fs::remove(NOTES_FILE);
        }
    }

} // namespace friday