#include "stdafx.h"
#include <iostream>
#include "mySlide.h"
#include "fileHandle.h"
using namespace std;

extern SDL_Event event;
extern const Uint8 *keyState;

void LoadMySlide(MySlide& _s, int slideNumber, std::string fileName, SDL_Renderer *renderer) {
    if(isFileSlideShow(fileName)){
        int numSlides = getNumSlides(fileName);
		if (numSlides < (slideNumber)) {
			std::cout << "Error Error Error slide number overflow" << std::endl;
			displaySlideNumOverflow(slideNumber);
		}
        else {
			_s.fileName = fileName;
            _s.renderer = renderer;
            int id = getIdFromSlide(fileName, slideNumber);
            _s.slide.setId(id);
			_s.id = id;
            Slide tmp;
            loadSlideWithId(tmp, fileName, id);
            _s.slide = tmp;
            unsigned long numImages = tmp.getSize(IMAGE);
            unsigned long numTexts = tmp.getSize(TEXT);
            unsigned long numSounds = tmp.getSize(SOUND);
            for ( unsigned long i = 0; i < numImages; i++ ) {
                vector<string> tmpVec = _s.slide.getVector(i , IMAGE);
                MyImage tmpImg;
                _s.images.push_back(tmpImg);
				_s.images[i].setInfo(tmpVec);
				_s.images[i].setTexture(_s.renderer);
            }
            for(unsigned long i = 0; i < numTexts; i++) {
                vector<string> tmpVec = _s.slide.getVector(i, TEXT);
                MyText tmpTxt;
				_s.texts.push_back(tmpTxt);
				_s.texts[i].setInfo(tmpVec);
				_s.texts[i].init(_s.renderer);
            }
            for(unsigned long i = 0; i < numSounds; i++) {
                vector<string> tmpVec = _s.slide.getVector(i, SOUND);
                MySound tmpSound;
				_s.sounds.push_back(tmpSound);
				_s.sounds[i].setInfo(tmpVec);
            }
        }
		_s.slide.setId(getIdFromSlide(fileName, slideNumber));
		_s.setPriority();
		_s.sortedImagesIndex = _s.getImageSorted();
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
			images[i].checkToDelete(this->fileName);
            break;
        }
    }
    for(unsigned long i = 0; i < texts.size(); i++) {
        texts[i].checkAndMove();
		if (texts[i].text.clicked)
			texts[i].checkAndDelete(this->fileName);
    }
    for(unsigned long i = 0; i < sounds.size(); i++) {
        sounds[i].processButton();
		if (sounds[i].button.clickedToMove)
			sounds[i].checkAndDelete(this->fileName);
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

std::string MySlide::getStringOfImageWithName(std::string fName){
	for (unsigned long i = 0; i < images.size(); i++) {
		std::string tmpName = images[i].path;
		if (fName == tmpName)
			return images[i].current;
	}
	return "*** Not Found ***";
}

std::string MySlide::getStringOfTextWithName(std::string fName) {
	for (unsigned long i = 0; i < texts.size(); i++) {
		std::string tmpText = texts[i].text.text;
		if (fName == tmpText)
			return texts[i].current;
	}
	return "*** Not Found ***";
}

std::string MySlide::getStringOfSoundWithName(std::string _text) {
	for (unsigned long i = 0; i < sounds.size(); i++) {
		std::string tmpText = sounds[i].text;
		if (_text == tmpText)
			return sounds[i].current;
	}
	return "*** Not Found ***";
}

int MySlide::getTotalResources()
{
	return images.size() + texts.size() + sounds.size();
}
