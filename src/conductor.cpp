#include <vector>
#include <raylib-cpp.hpp>
#include <iostream>

using namespace std;

class conductor
{
private:
    double _lastTime;
    int step;

    void updateCurStep();
public:
    conductor(vector<raylib::Music *> tracks);
    ~conductor();
    void update();

    int getStep();

    vector<raylib::Music *> tracks;
    double time;
    short bpm;
};

conductor::conductor(vector<raylib::Music *> tracks)
{
    this->tracks = tracks;
}

conductor::~conductor()
{
}


void conductor::update(){
    for(auto track : tracks){
        double resyncTimer = 0;
        if(track->GetTimePlayed() == _lastTime){
            resyncTimer += GetFrameTime() * 0.001;
        }
        else{
            resyncTimer = 0;
        }
        time = track->GetTimePlayed() + resyncTimer;
        _lastTime = track->GetTimePlayed();
    }
    updateCurStep();
}

int conductor::getStep(){
    return step;
}

void conductor::updateCurStep(){
    
}