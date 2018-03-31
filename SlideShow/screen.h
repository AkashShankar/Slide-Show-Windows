#pragma once
#include <SDL.h>
#include <string>

const int mainScreenWidth = 1300 , mainScreenHeight = 810;
const int inputScreenWidth = 500, inputScreenHeight = 500;

class Screen {
private:
    SDL_Texture *texture;
    SDL_Renderer *renderer;
    SDL_Window *window;
    Uint32 *screenBuffer;
    Uint32 alpha;
    std::string title;
    int x , y;
private:
    void setWidth(int width);
    void setHeight(int height);
    void setTitle(std::string title);
    void setPosition(int x, int y);
public:
    Screen(std::string title , int x, int y, int w, int h);
    bool init();
    void setPixel(int x, int y, int r, int g, int b, int a);
    void setPixel(int x, int y, SDL_Color color);
    void drawRect(int x, int y, int w, int h, SDL_Color color);
    inline Uint32* getPixels() { return screenBuffer; }
    SDL_Renderer* getRenderer();
    SDL_Window* getWindow();
    int getWidth();
    int getHeight();
    void render(void(*renderFunction)(void));
    void destroy();
    void clearScreen();
public:
    int width;
    int height;
    int windowId;
    bool mouseFocus;
    bool keyboardFocus;
    bool minimized;
    bool shown;
};

void initBothScreens();
void destroyBothScreens();
