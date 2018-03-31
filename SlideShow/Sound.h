#pragma once
#include <SDL_mixer.h>
#include <string>
#include "utilities.h"

class Sound {
private:
    Mix_Music *music{nullptr};
    std::string path;
public:
    Timer timer;
    Sound(std::string path);
    Sound() { path = ""; };
    void setStartTime(double s);
    void setResetTime(double r);
    void setPath(std::string path);
    void process();
    void start();
    void init();
    void destroy();
};
