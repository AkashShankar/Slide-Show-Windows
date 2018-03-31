#include "stdafx.h"
#include <iostream>
#include "Image.h"
using namespace std;

extern SDL_Rect upperBorder;
extern SDL_Rect leftBorder;
extern SDL_Event event;

Image::Image(){
    pixelFormat = SDL_PIXELFORMAT_RGBA8888;
    renderer = nullptr;
}

void Image::setPath(std::string path){
    SDL_Surface *tmp = IMG_Load(path.c_str());
    if(!tmp) {
        cout << "IMG : " << IMG_GetError() << endl;
        return;
    }
    if(this->renderer == nullptr)
        cout << "Renderer not set : Texture not created" << endl;
    else {
        SDL_Surface *formatted = SDL_ConvertSurfaceFormat(tmp, pixelFormat, 0);
        this->texture = SDL_CreateTexture(renderer, pixelFormat,
                                          SDL_TEXTUREACCESS_STREAMING,
                                          formatted->w, formatted->h);
        SDL_LockTexture(texture, NULL, &buffer, &pitch);
        memcpy(buffer, formatted->pixels, pitch * formatted->h);
        SDL_UnlockTexture(texture);
        buffer = nullptr;
        pitch = 0;
        width = formatted->w;
        height = formatted->h;
        SDL_FreeSurface(tmp);
        SDL_FreeSurface(formatted);
        SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
    }
}

void Image::checkAndMove() { // Working Properly
    int x, y;
    if(event.type == SDL_MOUSEMOTION || event.type == SDL_MOUSEBUTTONUP
       || event.type == SDL_MOUSEBUTTONDOWN) {
        if(event.type == SDL_MOUSEBUTTONDOWN){
            SDL_GetMouseState(&x, &y);
            if(isMouseOn(x, y)) {
                clicked = true;
            }
        }
        if(event.type == SDL_MOUSEBUTTONUP) {
            clicked = false;
        }
        if(clicked) {
            SDL_GetMouseState(&x, &y);
            desRect.x = x;
            desRect.y = y;
        }
    }
    adjustDesRect();
}

bool Image::isMouseOn(int x, int y) {
    if(x > desRect.x && x < desRect.x + desRect.w
       && y > desRect.y && y < desRect.y + desRect.h)
        return true;
    return false;
}

void Image::setAlpha(int alpha){
    if(alpha > 255)
        alpha = 255;
    else if(alpha < 0)
        alpha = 1;
    else
        this->alpha = alpha;
}

void Image::changeAlpha_Image(bool increase){
    int tmp = alpha;
    if(increase)
        setAlpha(++tmp);
    else
        setAlpha(--tmp);
}

void Image::destroy() {
    if(texture != nullptr)
        SDL_DestroyTexture(texture);
}

void Image::renderDes() {
    SDL_RenderCopy(renderer, texture, NULL, &desRect);
    SDL_SetTextureAlphaMod(texture, alpha);
}

void Image::renderBoth() {
    SDL_RenderCopy(renderer, texture, &srcRect, &desRect);
    SDL_SetTextureAlphaMod(texture, alpha);
}

void Image::renderNone() {
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_SetTextureAlphaMod(texture, alpha);
}

void Image::setRenderer(SDL_Renderer *renderer) {
    this->renderer = renderer;
}

void Image::setDesRect(int x, int y, int w, int h) {
    desRect = {x, y, w, h};
}

void Image::adjustDesRect(){
    if( desRect.x < leftBorder.x ){
        desRect.x = leftBorder.x + 10;
    }
    if( desRect.y < upperBorder.y ){
        desRect.y = upperBorder.y + 10;
    }
}

void Image::setSrcRect(int x, int y, int w, int h) {
    srcRect = {x, y, w, h};
}
