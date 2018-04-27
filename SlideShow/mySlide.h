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
	std::vector<int> sortedImagesIndex;
public:
	std::string fileName;
	int id = -1;
public:
    friend void LoadMySlide(MySlide& _s, int slideNumber , std::string fileName, SDL_Renderer *renderer);
	void displayInfo();
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
	void insert(std::string _txt);
	std::string getStringOfImageWithName(std::string fName);
	std::string getStringOfTextWithName(std::string fName);
	std::string getStringOfSoundWithName(std::string _text);
	int getTotalResources();
};
