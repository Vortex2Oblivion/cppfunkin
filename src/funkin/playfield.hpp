#pragma once

#include "../engine/group.hpp"
#include "character.hpp"
#include "conductor.hpp"
#include "note.hpp"
#include "song.hpp"

namespace funkin {
class PlayField : public engine::Group<engine::Object> {
   protected:
    const std::vector<std::string> singAnimArray = {"singLEFT", "singDOWN", "singUP", "singRIGHT"};
    std::vector<bool> justHitArray = {false, false, false, false};
    std::vector<bool> pressedArray = {false, false, false, false};
    std::vector<funkin::NoteData> noteDatas = {};
    std::vector<funkin::Note*> toInvalidate = {};
    size_t noteDataIndex = 0;

    void invalidateNote(Note* note);
    void calculateAccuracy();

   public:
    PlayField(float x, float y, std::vector<NoteData> noteDatas, std::vector<Character*> characters, bool cpuControlled = false);
    ~PlayField();

    bool cpuControlled = false;
    float scrollSpeed = 1.0f;
    float accuracy = 100.0f;
    unsigned int misses = 0;
    int score = 0;
    float health = 50.0f;

    float minHitTime = 180.0f;
    float maxHitTime = 180.0f;

    engine::Group<funkin::Note>* notes;
    engine::Group<funkin::StrumNote>* strums;
    std::vector<funkin::Character*> characters = {};

    funkin::Conductor* conductor;

    void generateStaticArrows(bool player);
    void update(float delta);
};
}  // namespace funkin
