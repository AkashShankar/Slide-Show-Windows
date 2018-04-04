#pragma once

#include "mySlide.h"

class SlideShow {
private:
	std::vector<MySlide> _slides;
	int currentSlideId{ -1 };
	std::string fileName;
public:
	inline void setFile(std::string) { this->fileName = fileName; }
	void addSlide(MySlide& _s);
	void processSlide(int id);
	void renderSlide(int id);
	void destroySlide(int id);
	int getIndexFromId(int id);
	void loadSlide(int id);
};
