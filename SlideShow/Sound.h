#pragma once
#include <SDL_mixer.h>
#include <string>
#include "utilities.h"

class Sound {
private:
    Mix_Music *music{nullptr};
    std::string path;
public:
    Sound(std::string path);
    Sound() { path = ""; };
	inline Mix_Music* get_music() { return music; }
	void setPath(std::string path);
	void init();
	void destroy();
	static bool ifSoundExists(std::string _fName);
};
