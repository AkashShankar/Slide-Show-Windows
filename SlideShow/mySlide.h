#pragma once
#include <vector>
#include "fileHandle.h"
#include "myImage.h"
#include "myText.h"
#include "mySound.h"

class MySlide{
private:
    Slide slide;
    SDL_Renderer *renderer = nullptr;
    std::vector<MyImage> images;
    std::vector<MyText> texts;
    std::vector<MySound> sounds;
    std::vector<int> imagePriority;
public:
	std::string fileName;
	int id = -1;
public:
    void loadSlide(int slideNumber , std::string fileName, SDL_Renderer *renderer);
    inline Slide getSlide() { return this->slide; };
	inline MyImage getImage(int index) { return images[index]; }
	inline MyText getText(int index) { return texts[index]; }
	inline MySound getSound(int index) { return sounds[index]; }
	void save(std::string fileName);
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
