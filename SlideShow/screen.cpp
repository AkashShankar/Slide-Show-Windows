#include "stdafx.h"
#include <iostream>
#include "initApi.h"
#include "screen.h"

/* global Screen variables */
Screen mainScreen("SlideShow", 50, 50, mainScreenWidth, mainScreenHeight);
Screen inputScreen("Alert", 200, 200, inputScreenWidth, inputScreenHeight);
/* global Screen variables */

/* other Functions */
void initBothScreens(){
    mainScreen.init();
    inputScreen.init();
}

void destroyBothScreens(){
    mainScreen.destroy();
    inputScreen.destroy();
}
/* other Functions */

Screen::Screen(std::string title , int x, int y, int w, int h){
    setTitle(title);
    setPosition(x, y);
    setWidth(w);
    setHeight(h);
}

bool Screen::init(){
    window = SDL_CreateWindow(title.c_str(), x, y, width, height, SDL_WINDOW_SHOWN);
    if(!window){
        std::cout << "window not created (Screen::init)" << std::endl;
        return false;
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(!renderer){
        std::cout << "renderer not created (Screen::init)" << std::endl;
        return false;
    }
    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888,
                                SDL_TEXTUREACCESS_STATIC, width, height);
    if(!texture){
        std::cout << "screen texture not created (Screen::init)" << std::endl;
        return false;
    }
    windowId = SDL_GetWindowID(window);
    screenBuffer = new Uint32[width * height];
    memset(screenBuffer, 255, width * height * sizeof(Uint32));
    mouseFocus = shown = true;
    return true;
}

void Screen::render(void(*renderFunction)(void)) {
    SDL_UpdateTexture(texture, NULL, screenBuffer, sizeof(Uint32) * width);
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_SetTextureAlphaMod(texture, alpha);
    renderFunction();
    SDL_RenderPresent(renderer);
}

void Screen::clearScreen() {
    memset(screenBuffer, 220, sizeof(Uint32) * width * height);
}

SDL_Renderer* Screen::getRenderer() {
    return renderer;
}

SDL_Window* Screen::getWindow() {
    return window;
}

void Screen::setWidth(int width){
    this->width = width;
}

void Screen::setHeight(int height){
    this->height = height;
}

void Screen::setTitle(std::string title){
    this->title = title;
}

void Screen::setPosition(int x, int y){
    this->x = x;
    this->y = y;
}

int Screen::getWidth(){
    return this->width;
}

int Screen::getHeight(){
    return this->height;
}

void Screen::setPixel(int x, int y, int r, int g, int b, int a){
    if(x < 0 || x > getWidth() || y < 0 || y > getHeight())
        return;
    Uint32 color = 0;
    color += r;
    color <<= 8;
    color += g;
    color <<= 8;
    color += b;
    color <<= 8;
    color += a;
    screenBuffer[y * getWidth() + x] = color;
}

void Screen::setPixel(int x, int y, SDL_Color color){
    if(x < 0 || x > getWidth() || y < 0 || y > getHeight())
        return;
    Uint32 col = 0;
    col += color.r;
    col <<= 8;
    col += color.g;
    col <<= 8;
    col += color.b;
    col <<= 8;
    col += color.a;
    screenBuffer[y * getWidth() + x] = col;
}

void Screen::drawRect(int x, int y, int w, int h, SDL_Color color){
    int xTo = x + w;
    int yTo = y + h;
    for( int i = x; i < xTo; i++ ){
        for( int j = y; j < yTo; j++ ){
            setPixel(i, j, color);
        }
    }
}

void Screen::destroy(){
    if(texture != nullptr){
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }
    if(renderer != nullptr){
        SDL_DestroyRenderer(renderer);
        renderer = nullptr;
    }
    if(window != nullptr){
        SDL_DestroyWindow(window);
        window = nullptr;
    }
    if(screenBuffer != nullptr){
        delete []screenBuffer;
    }
}
