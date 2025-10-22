#include "conductor.hpp"
#include <cstdlib>
#include <raylib-cpp.hpp>
#include <vector>

funkin::Conductor::Conductor() { this->tracks = {}; }

funkin::Conductor::Conductor(std::vector<raylib::Music*> tracks) { this->tracks = tracks; }

funkin::Conductor::~Conductor() {
    if (tracks.empty()) {
        return;
    }
    for (auto track : tracks) {
        track->Stop();
        delete track;
    }
    tracks.clear();
}

void funkin::Conductor::start(std::vector<raylib::Music*> tracks) {
    this->tracks = tracks;
    start();
}

void funkin::Conductor::start() {
    if (tracks.empty()) {
        return;
    }
    for (auto track : tracks) {
        track->Play();
    }
}

void funkin::Conductor::stop() {
    if (tracks.empty()) {
        return;
    }
    for (auto track : tracks) {
        track->Stop();
    }
}

void funkin::Conductor::update(float delta) {
    if (tracks.empty()) {
        return;
    }
    for (auto track : tracks)
    {
        track->Update();
    }
    auto track = tracks[0];
    #if __APPLE__
    if (track->GetTimePlayed() >= time || abs(time - track->GetTimePlayed()) > 20.0f / 1000.0f)
    #else
    if (track->GetTimePlayed() != lastAudioTime)
    #endif
    {
        time = track->GetTimePlayed();
    }
    else if (track->IsPlaying())
    {
        time += delta;
    }
    lastAudioTime = track->GetTimePlayed();

    int oldStep = step;
    int oldBeat = beat;
    updateStep();
    updateBeat();
    if (oldStep < step) {
        stepHit();
    }

    if (oldBeat < beat) {
        beatHit();
    }
}

int funkin::Conductor::getBeat() { return beat; }

int funkin::Conductor::getStep() { return step; }

float funkin::Conductor::getCrochet() { return (60.0f / bpm); }

float funkin::Conductor::getStepCrochet() { return getCrochet() / 4; }

void funkin::Conductor::updateStep() { step = (int)(time / getStepCrochet()); }

void funkin::Conductor::updateBeat() { beat = (int)(time / getCrochet()); }

void funkin::Conductor::stepHit()
{
}

void funkin::Conductor::beatHit() {}

float funkin::Conductor::getMinAudioTime() {
    if (tracks.empty()) {
        return 0.0f;
    }
    float minAudioTime = getMaxAudioTime();
    for (auto track : tracks) {
        if (track->GetTimeLength() < minAudioTime) {
            minAudioTime = track->GetTimeLength();
        }
    }
    return minAudioTime;
}

float funkin::Conductor::getMaxAudioTime() {
    if (tracks.empty()) {
        return 0.0f;
    }
    float maxAudioTime = 0.0f;
    for (auto track : tracks) {
        if (track->GetTimeLength() >= maxAudioTime) {
            maxAudioTime = track->GetTimeLength();
        }
    }
    return maxAudioTime;
}
