#include "stdafx.h"
#include <iostream>
#include "Sound.h"

Sound::Sound(std::string path) {
    this->path = path;
}
void Sound::setStartTime(double s) {
    timer.setStartTime(s);
}

void Sound::setResetTime(double r) {
    timer.setResetTime(r);
}

void Sound::init() {
    music = Mix_LoadMUS(path.c_str());
    if(!music) {
        std::cout << "Mixer: " << Mix_GetError() << std::endl;
        return;
    }
}

void Sound::setPath(std::string path) {
    this->path = path;
}

void Sound::start() {
    timer.startClock();
}

void Sound::destroy() {
    if(music != nullptr)
        Mix_FreeMusic(music);
}

void Sound::process() {
    if(timer.hasStarted) {
        if(!Mix_PlayingMusic()) {
            Mix_PlayMusic(music, -1);
        }
        else if(Mix_PausedMusic()) {
            Mix_ResumeMusic();
        }
    }
    else {
        Mix_PauseMusic();
    }
}
