/*
  1) setRenderer()
  2) setPath()
  3) setDesRect() / setSrcRect()
  4) renderNone() / renderDes() / renderBoth()
*/
#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <string>

class Image {
private:
    SDL_Texture *texture = nullptr;
    SDL_Renderer *renderer = nullptr;
    Uint32 pixelFormat = SDL_PIXELFORMAT_RGBA8888;
    Uint32 currentColor = 0;
    Uint32 toColor = 0;
    void *buffer = nullptr;
    Uint8 alpha = 255;
    int pitch = 0;
    int width;
    int height;
    int colorRange = 15;
public:
	bool clicked{ false };
	void(*action)(void) { nullptr };
	SDL_Rect srcRect = { 0,0,0,0 };
	SDL_Rect desRect = { 0,0,0,0 };
public:
    Image();
    void setPath(std::string path);
    void setRenderer(SDL_Renderer *renderer);
    void setDesRect(int x, int y, int w, int h);
    void setSrcRect(int x, int y, int w, int h);
    bool isMouseOn(int x, int y);
    void setAlpha(int alpha);
    void changeAlpha_Image(bool increase);
    void checkAndMove();
	void checkToAction();
    void adjustDesRect();
    void renderDes();
    void renderBoth();
    void renderNone();
    void destroy();
};
