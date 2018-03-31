#pragma once
#include <vector>
#include "fileHandle.h"
#include "myImage.h"
#include "myText.h"
#include "mySound.h"

class MySlide{
private:
    Slide slide;
    std::string fileName;
    int id = -1;
    SDL_Renderer *renderer = nullptr;
    std::vector<MyImage> images;
    std::vector<MyText> texts;
    std::vector<MySound> sounds;
    std::vector<int> imagePriority;
public:
    friend void loadSlide(MySlide &slide, int slideNumber , std::string fileName, SDL_Renderer *renderer);
    inline Slide getSlide() { return this->slide; };
    void renderSlide();
    void setPriority();
    void checkAndBringToFront();
    void setHighestPriorityToImageWithIndex(int index);
    void checkAndChangeAlpha(int index);
    std::vector<int> getImageSorted();
    void update();
    void process();
    void destroy();
};
