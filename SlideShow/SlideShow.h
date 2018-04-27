#pragma once

#include "mySlide.h"

class SlideShow {
private:
	int currentSlideId{ -1 };
	int currentIndex{ -1 };
public:
	std::string fileName;
	std::vector<MySlide> _slides;
public:
	inline void setFile(std::string fileName) { this->fileName = fileName; }
	inline int getTotalSlides() { return _slides.size(); }
	void setCurrentId(int id);
	void processSlide();
	void renderSlide();
	void destroySlide();
	void updateSlide();
	int getIndexFromId(int id);
	void loadSlide();
	MySlide getCurrentSlide();
	int getAllResources();
};
