#include "stdafx.h"
#include <iostream>
#include "Sound.h"

Sound::Sound(std::string path) {
    this->path = path;
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

void Sound::destroy() {
	if (music != nullptr) {
		Mix_FreeMusic(music);
	}
	music = nullptr;
}

bool Sound::ifSoundExists(std::string _fName) {
	Mix_Music *tmpMusic = nullptr;
	tmpMusic = Mix_LoadMUS(_fName.c_str());
	bool exists = true;
	if (!tmpMusic)
		exists = false;
	Mix_FreeMusic(tmpMusic);
	return exists;
}
