#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include "utilities.h"

class Text {
private:
    SDL_Texture *texture;
    TTF_Font *font;
    SDL_Color fontColor;
    std::string text;
    std::string fontPath;
public:
	int fontSize;
    SDL_Renderer *renderer;
    bool clicked = false;
	SDL_Rect rect;
public:
    Text(std::string fontPath, int fontSize);
    Text() {}
    void setText(std::string text);
    void setRenderer(SDL_Renderer *renderer);
    void setPos(int x, int y);
    void setCol(Color c);
    inline void setPath(std::string path) { fontPath = path; }
    inline void setFontSize(int size) { fontSize = size; }
    void checkAndMove();
    bool isMouseOn(int x, int y);
    void adjustDesRect();
    inline SDL_Color getColor() { return fontColor; }
    void render();
    void init();
	void reinit();
    void destroy();
	static bool ifTextExists(std::string _fName);
};
