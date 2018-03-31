#pragma once

#include <string>
#include <vector>
#include "Image.h"
#include "utilities.h"

class MyImage: public Image
{
private:
    SDL_Rect rect;
    std::string path;
    Resource resType;
    //Image img;
public:
    void setInfo(std::vector<std::string> sl);
    void setTexture(SDL_Renderer *renderer);
    void checkAndMove();
    bool clicked();
    void changeAlpha_MyImage(bool increase);
    void displayInfo();
    void renderDes();
    void destroy();
};
