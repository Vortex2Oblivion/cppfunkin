#pragma once

#include "../engine/group.hpp"
#include "character.hpp"
#include "conductor.hpp"
#include "note.hpp"
#include "song.hpp"

namespace funkin {
class PlayField final : public engine::Group<engine::Object> {
   protected:
    const std::array<std::string, 4> singAnimArray = {"singLEFT", "singDOWN", "singUP", "singRIGHT"};
    std::array<bool, 4> justHitArray = {false, false, false, false};
    std::array<bool, 4> pressedArray = {false, false, false, false};
    std::vector<funkin::NoteData> noteDatas = {};
    std::vector<std::shared_ptr<funkin::Note>> toInvalidate = {};
    size_t noteDataIndex = 0;
    std::array<std::shared_ptr<funkin::Note>, 4> lastSpawnedNotes = std::array<std::shared_ptr<funkin::Note>, 4>();

    void invalidateNote(const std::shared_ptr<funkin::Note> &note) const;
    void calculateAccuracy();

   public:
    PlayField(float x, float y, std::vector<NoteData> noteDatas, std::vector<std::shared_ptr<funkin::Character>> characters, bool cpuControlled = false);
    ~PlayField() override;

    bool cpuControlled = false;
    float scrollSpeed = 1.0f;
    float accuracy = 100.0f;
    size_t misses = 0;
    int score = 0;
    float health = 50.0f;

    float minHitTime = 180.0f;
    float maxHitTime = 180.0f;

    std::shared_ptr<engine::Group<funkin::Note>> notes;
    std::shared_ptr<engine::Group<funkin::StrumNote>> strums;
    std::vector<std::shared_ptr<funkin::Character>> characters = {};

    std::shared_ptr<funkin::Conductor> conductor = nullptr;

    void generateStaticArrows() const;
    void update(float delta) override;
};
}  // namespace funkin
