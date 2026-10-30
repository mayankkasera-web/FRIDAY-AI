// FRIDAY AI — Notes module declarations
#pragma once

#include <string>
#include <vector>

namespace friday
{

    struct Note
    {
        std::string timestamp;
        std::string text;
    };

    void saveNote(const std::string &text);
    std::vector<Note> loadNotes();
    void clearNotes();

} // namespace friday