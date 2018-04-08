#include "stdafx.h"
#include "initApi.h"
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

bool initSDL(){
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0){
        std::cout << "SDL Not Initialised" << std::endl;
        return false;
    }
    std::cout << "SDL Initialised" << std::endl;
    return true;
}

bool initImage(){
    int flags = IMG_INIT_JPG | IMG_INIT_JPG | IMG_INIT_TIF;
    if(IMG_Init(flags) != flags){
        std::cout << "IMG Not initialised" << std::endl;
        return false;
    }
    std::cout << "IMG Initialised" << std::endl;
    return true;
}

bool initTTF(){
    if(TTF_Init() < 0){
        std::cout << "TTF Not initialised" << std::endl;
        return false;
    }
    std::cout << "TTF Initialised" << std::endl;
    return true;
}

bool initAllApi(){
    if(!initSDL())
        return false;
    if(!initImage())
        return false;
    if(!initTTF())
        return false;
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
	std::cout << "------------------" << std::endl;
    return true;
}

void closeAllApi(){
    SDL_Quit();
    IMG_Quit();
    TTF_Quit();
    std::cout << "All api's closed" << std::endl;
}

