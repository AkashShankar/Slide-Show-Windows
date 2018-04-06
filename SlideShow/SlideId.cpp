#include "stdafx.h"
#include "SlideId.h"
#include <iostream>

const char* e2 = "Num Slides error";

void SlideId::loadAllIds()
{
	int numSlides = getNumSlides(fileName);
	if (numSlides == -1)
		throw e2;
	for (int i = 0; i < numSlides; i++) {
		int _tmpId = getSlideIdNumber(fileName, i + 1);
		_ids.push_back(_tmpId);
	}
	std::cout << "All slide id's loaded/refreshed. Total: " << numSlides << std::endl;
}

void SlideId::increment() {
	if (currentIndex < getNumIds() - 1) {
		currentIndex++;
		currentId = _ids[currentIndex];
	}
}

void SlideId::decrement() {
	if (currentIndex > 0) {
		currentIndex--;
		currentId = _ids[currentIndex];
	}
}

void SlideId::displayAllIds() {
	for (unsigned long i = 0; i < _ids.size(); i++) {
		std::cout << (i + 1) << ": " << _ids[i] << std::endl;
	}
}

void SlideId::displayCurrent() {
	std::cout << "CurrentId: " << currentId << std::endl;
	std::cout << "CurrentIndex: " << currentIndex << std::endl;
}