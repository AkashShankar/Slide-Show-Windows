#include "stdafx.h"
#include "SlideShow.h"
#include "fileHandle.h"
#include "screen.h"
#include <iostream>

extern Screen mainScreen;

const char* e1 = "Slide with id cannot be processed";

int SlideShow::getIndexFromId(int id) {
	int numSlides = getNumSlides(fileName);
	for (int i = 0; i < numSlides; i++) {
		int _tmpId = getSlideIdNumber(fileName, i + 1);
		if (_tmpId == id) {
			return i;
		}
	}
	return -1;
}

void SlideShow::setCurrentId(int id) {
	if (ifSlideIdExists(fileName, id)) {
		this->currentSlideId = id;
		currentIndex = getIndexFromId(id);
	}
	else {
		throw e1;
	}
}

void SlideShow::updateSlide() {
	_slides[currentIndex].update();
}

void SlideShow::loadSlide() {
	MySlide tmpSlide;
	tmpSlide.loadSlide(currentIndex + 1, fileName, mainScreen.getRenderer());
	_slides.push_back(tmpSlide);
}

void SlideShow::processSlide() {
	_slides[currentIndex].process();
}

void SlideShow::renderSlide() {
	_slides[currentIndex].renderSlide();
}

void SlideShow::destroySlide() {
	for(unsigned long i = 0; i < _slides.size(); i++)
		_slides[i].destroy();
}

MySlide SlideShow::getCurrentSlide() {
	return _slides[currentIndex];
}