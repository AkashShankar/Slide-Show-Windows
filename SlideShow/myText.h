#pragma once
#include <vector>
#include "text.h"

class MyText {
private:
    Text text;
    Resource resType;
    int fontSize = 10;
    std::string fontPath;
    Color fontColor;
public:
    void setInfo(std::vector<std::string> sl);
    void init(SDL_Renderer *renderer);
    void checkAndMove();
    void render();
    void destroy();
};

