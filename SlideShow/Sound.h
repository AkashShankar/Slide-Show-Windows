#pragma once
#include <SDL_mixer.h>
#include <string>
#include "utilities.h"

class Sound {
private:
    Mix_Music *music{nullptr};
    std::string path;
public:
    //Timer timer;
    Sound(std::string path);
    Sound() { path = ""; };
	inline Mix_Music* get_music() { return music; }
	void setPath(std::string path);
	void init();
	void destroy();

    //void setStartTime(double s);
    //void setResetTime(double r);
    //void process();
    //void start();
};
