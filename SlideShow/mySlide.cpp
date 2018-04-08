#include "stdafx.h"
#include <iostream>
#include "mySlide.h"
#include "fileHandle.h"
using namespace std;

extern SDL_Event event;
extern const Uint8 *keyState;

void MySlide::loadSlide(int slideNumber, std::string fileName, SDL_Renderer *renderer) {
    if(isFileSlideShow(fileName)){
        int numSlides = getNumSlides(fileName);
		if (numSlides < (slideNumber)) {
			std::cout << "Error Error Error slide number overflow" << std::endl;
			displaySlideNumOverflow(slideNumber);
		}
        else {
			this->fileName = fileName;
            this->renderer = renderer;
            int id = getIdFromSlide(fileName, slideNumber);
            this->slide.setId(id);
			this->id = id;
            Slide tmp;
            loadSlideWithId(tmp, fileName, id);
            this->slide = tmp;
            unsigned long numImages = tmp.getSize(IMAGE);
            unsigned long numTexts = tmp.getSize(TEXT);
            unsigned long numSounds = tmp.getSize(SOUND);
            for ( unsigned long i = 0; i < numImages; i++ ) {
                vector<string> tmpVec =this->slide.getVector(i , IMAGE);
                MyImage tmpImg;
                this->images.push_back(tmpImg);
				this->images[i].setInfo(tmpVec);
				this->images[i].setTexture(this->renderer);
            }
            for(unsigned long i = 0; i < numTexts; i++) {
                vector<string> tmpVec = this->slide.getVector(i, TEXT);
                MyText tmpTxt;
				this->texts.push_back(tmpTxt);
				this->texts[i].setInfo(tmpVec);
				this->texts[i].init(this->renderer);
            }
            for(unsigned long i = 0; i < numSounds; i++) {
                vector<string> tmpVec = this->slide.getVector(i, SOUND);
                MySound tmpSound;
				this->sounds.push_back(tmpSound);
				this->sounds[i].setInfo(tmpVec);
            }
        }
		this->slide.setId(getIdFromSlide(fileName, slideNumber));
		this->setPriority();
        sortedImagesIndex = this->getImageSorted();
    }
    else
        displayFileNotSlideShow(fileName);
}

void MySlide::displayInfo()
{
	int numImages = images.size();
	int numSounds = sounds.size();
	int numTexts = texts.size();
	for (int i = 0; i < numImages; i++) {
		images[i].displayInfo();
	}
}

void MySlide::save(std::string fileName) {
	for (unsigned long i = 0; i < images.size(); i++)
		images[i].save(fileName);
	for (unsigned long i = 0; i < sounds.size(); i++)
		sounds[i].save(fileName);
	for (unsigned long i = 0; i < texts.size(); i++)
		texts[i].save(fileName);
}

void MySlide::process(){
    checkAndBringToFront();
    for(unsigned long i = 0; i < images.size(); i++) {
        images[i].checkAndMove();
        if(images[i].clicked())
        {
            checkAndChangeAlpha(i);
            break;
        }
    }
    for(unsigned long i = 0; i < texts.size(); i++) {
        texts[i].checkAndMove();
    }
    for(unsigned long i = 0; i < sounds.size(); i++) {
        sounds[i].processButton();
    }
}

void MySlide::setPriority(){
    for(unsigned long i = 0; i < images.size(); i++) {
        int toPush = (int)(images.size() - i - 1);
        imagePriority.push_back(toPush);
    }
}

void MySlide::checkAndBringToFront() {
    for(unsigned long i = 0; i < images.size(); i++) {
        if(images[i].clicked()) {
            if(keyState[SDL_SCANCODE_0]) {
                setHighestPriorityToImageWithIndex(i);
                sortedImagesIndex = getImageSorted();
            }
            break;
        }
    }
}

void MySlide::update() {
    for(unsigned long i = 0; i < sounds.size(); i++) {
		sounds[i].processSound();
    }
}

void MySlide::checkAndChangeAlpha(int index){
    if(keyState[SDL_SCANCODE_P])
        images[index].changeAlpha_MyImage(true); // Increase alpha
    else if(keyState[SDL_SCANCODE_O])
        images[index].changeAlpha_MyImage(false); // Decrease alpha
}

void MySlide::setHighestPriorityToImageWithIndex(int index) {
    int tmp = 0, tmpIndex = 0;
    for(unsigned long i = 0; i < images.size(); i++) {
        if(imagePriority[i] == 0) {
            tmpIndex = i;
            tmp = imagePriority[i];
        }
    }
    imagePriority[tmpIndex] = imagePriority[index];
    imagePriority[index] = 0;
}

long getIndex(vector<int> v, int ele) {
    auto it = find(v.begin(), v.end(), ele);
    long index = distance(v.begin(), it);
    return index;
}

int getMaxAndDel(vector<int> &v) {
    int max = v[0];
    for(unsigned long i = 0; i < v.size() ; i++) {
        if(v[i] > max)
            max = v[i];
    }
    long index = getIndex(v, max);
    v.erase(v.begin() + index);
    return max;
}

vector<int> MySlide::getImageSorted() {
    vector<int> copy = imagePriority;
    vector<int> sorted;
    for(unsigned long i = 0; i < imagePriority.size(); i++) {
        int max = getMaxAndDel(copy);
        long index = getIndex(imagePriority, max);
        sorted.push_back((int)index);
    }
    return sorted;
}

void MySlide::renderSlide(){
    for(unsigned long i = 0; i < images.size(); i++) {
		int index = sortedImagesIndex[i];
        images[index].renderDes();
    }
    for(unsigned long i = 0; i < texts.size(); i++) {
        texts[i].render();
    }
    for(unsigned long i = 0; i < sounds.size(); i++) {
        sounds[i].renderButton();
    }
}

void MySlide::destroy(){
    for(unsigned long i = 0; i < images.size(); i++)
        images[i].destroy();
    for(unsigned long i = 0; i < texts.size(); i++)
        texts[i].destroy();
    for(unsigned long i = 0; i < sounds.size(); i++)
        sounds[i].destroy(); 
}

void MySlide::insert(std::string _txt) {
	putToSlideWithId(fileName, id, _txt);
}
