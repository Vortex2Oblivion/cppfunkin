#pragma once

#include "conductor.hpp"
#include "character.hpp"
#include "note.hpp"
#include "song.hpp"
#include "../engine/group.hpp"

namespace funkin
{
    class PlayField : public engine::Group<engine::Object>
    {
    protected:
        const std::vector<std::string> singAnimArray = {"singLEFT", "singDOWN", "singUP", "singRIGHT"};
        std::vector<bool> justHitArray = {false, false, false, false};
        std::vector<bool> pressedArray = {false, false, false, false};
        std::vector<funkin::NoteData> noteDatas = {};
        size_t noteDataIndex = 0;

        void invalidateNote(Note *note);
        void setup(std::vector<NoteData> noteDatas);

    public:
        PlayField(std::vector<NoteData> noteDatas);
        PlayField(std::vector<NoteData> noteDatas, std::vector<Character *> characters);
        ~PlayField();

        bool cpuControlled = false;
        float scrollSpeed = 2.3f;
        unsigned int misses = 0;
        int score = 0;

        engine::Group<funkin::Note> *notes;
        engine::Group<funkin::StrumNote> *strums;
        std::vector<funkin::Character *> characters = {};

        funkin::Conductor *conductor;

        void generateStaticArrows(bool player);
        void update(float delta);
    };
} // namespace funkin
