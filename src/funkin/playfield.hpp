#pragma once

#include "note.hpp"
#include "../engine/group.hpp"

namespace funkin
{
    class PlayField : public engine::Group<engine::Object>
    {
    private:
        /* data */
    public:
        PlayField(/* args */);
        ~PlayField();
        bool cpuControlled = true;
        engine::Group<Note> notes;
        engine::Group<StrumNote> strums;
        void update(float delta);
    };
} // namespace funkin
