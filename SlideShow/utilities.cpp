#include "stdafx.h"
#include <iostream>
#include <ctime>
#include "utilities.h"
#include "screen.h"
#include "SlideId.h"
#include "SlideShow.h"

extern Screen mainScreen;
extern SDL_Event event;
extern SlideId slideId;
extern SlideShow sl;
extern MySlide currentSlide;
extern const Uint8* keyState;
SDL_Rect screenShotRect;
SDL_Rect srcScreenShotRect;

void setColor(SDL_Color &color, Color c){
    if(c == RED)
        color =  {255,0,0,255};
    else if(c == BLUE)
        color = {0,0,255,255};
    else if(c == GREEN)
        color = {0,255,0,255};
    else if(c == YELLOW)
        color = {255,255,0,255};
    else if(c == BLACK)
        color = {0,0,0,255};
    else if(c == WHITE)
        color = {255,255,255,255};
    else if(c == GRAY)
        color = {100,100,100,255};
    else if(c == LBLUE)
        color = {0,255,255,255};
    else if(c == DPINK)
        color = {255,0,255,255};
    else if(c == MAGENTA)
        color = {100,0,255,255};
    else if(c == DGREEN)
        color = {0,75,75,255};
    else if(c == LPINK)
        color = {255,100,255,255};
    else if(c == OLIVE)
        color = {128,128,0,255};
    else if(c == MAROON)
        color = {128,0,0,255};
    else if(c == PURPLE)
        color = {128,0,128,255};
    else if(c == TEAL)
        color = {0,128,128,255};
    else if(c == NAVY)
        color = {0,0,128,255};
}

Color getColorFromString(std::string c){
    if(c == "RED")
        return RED;
    else if(c == "BLUE")
        return BLUE;
    else if(c == "GREEN")
        return GREEN;
    else if(c == "YELLOW")
        return YELLOW;
    else if(c == "BLACK")
        return BLACK;
    else if(c == "WHITE")
        return WHITE;
    else if(c == "GRAY")
        return GRAY;
    else if(c == "LBLUE")
        return LBLUE;
    else if(c == "DPINK")
        return DPINK;
    else if(c == "MAGENTA")
        return MAGENTA;
    else if(c == "DGREEN")
        return DGREEN;
    else if(c == "LPINK")
        return DGREEN;
    else if(c == "OLIVE")
        return OLIVE;
    else if(c == "MAROON")
        return MAROON;
    else if(c == "PURPLE")
        return PURPLE;
    else if(c == "TEAL")
        return TEAL;
    else if(c == "NAVY")
        return NAVY;
    return BLACK; // Default is black
}

SDL_Color getColorFromPixel(Uint32 number){
    SDL_Color tmpColor = {0,0,0,0};
    unsigned int red = number & 0xFF000000;
    red >>= 24;
    tmpColor.r = red;
    unsigned int green = number & 0x00FF0000;
    green >>= 16;
    tmpColor.g = green;
    unsigned int blue = number & 0x0000FF00;
    blue >>= 8;
    tmpColor.b = blue;
    unsigned int alpha = number & 0x000000FF;
    tmpColor.a = alpha;
    return tmpColor;
}

void putColorToPixel(Uint32 &number, SDL_Color color){
    number = 0;
    number += color.r;
    number <<= 8;
    number += color.g;
    number <<= 8;
    number += color.b;
    number <<= 8;
    number += color.a;
}

double map(double from, double fromRange, double toRange){
    return ( from / fromRange ) * toRange;
}

std::string getStringFromVector(std::vector<std::string> _t) {
	std::string _tmpStr;
	for (unsigned long i = 0; i < _t.size(); i++) {
		_tmpStr += _t[i];
		if (i != _t.size() - 1)
			_tmpStr += " ";
	}
	return _tmpStr;
}

bool checkIfNum(std::string _str) {
	for (unsigned long i = 0; i < _str.length(); i++) {
		if (!isalnum(_str[i]))
			return false;
	}
	return true;
}

void ScrollBar::setColor(Color c) {
	::setColor(_c, c);
}

void ScrollBar::draw() {
	mainScreen.drawRect(_rect.x, _rect.y, _rect.w, _rect.h, _c);
}

void ScrollBar::checkAndMove() {
	if (event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEBUTTONUP) {
		if (event.type == SDL_MOUSEBUTTONDOWN) {
			int x, y;
			SDL_GetMouseState(&x, &y);
			if (isMouseOnRect(x, y)) {
				clicked = true;
			}
		}
		if (event.type == SDL_MOUSEBUTTONUP)
			clicked = false;
	}
	if (clicked) {
		int x, y;
		SDL_GetMouseState(&x, &y);
		_rect.y = y - _rect.w + 10;
		adjustRect();
		calculateCurrentLevel();
	}
}

void ScrollBar::adjustRect() {
	if (_rect.y < upperBoundY)
		_rect.y = upperBoundY;
	else if (_rect.y > lowerBoundY)
		_rect.y = lowerBoundY;
}

void ScrollBar::initalise(ScreenShots & _sc) {
	totalLength = abs(upperBoundY - lowerBoundY);
	maxLevels = _sc.maxBulkIndex;
}

void ScrollBar::calculateCurrentLevel() {
	currentLength = abs(upperBoundY - _rect.y);
	double per = totalLength / maxLevels;
	currentLevel = (int)(ceil(currentLength / per));
	if (currentLevel == 0)
		currentLevel = 1;
}

void ScrollBar::setBounds(int upper, int lower) {
	upperBoundY = upper;
	lowerBoundY = lower;
}

void ScrollBar::set(int x, int y, int w, int h) {
	_rect = { x, y, w, h };
}

bool ScrollBar::isMouseOnRect(int x, int y) {
	if (x > _rect.x && x < _rect.x + _rect.w
		&& y > _rect.y && y < _rect.y + _rect.h)
		return true;
	return false;
}
ScreenShots::ScreenShots() {
	screenShotRect = { 300, 100, mainScreenWidth - 300, mainScreenHeight };
	srcScreenShotRect = { 0, 0, mainScreenWidth - 300, mainScreenHeight - 100 };
}

void ScreenShots::set(int x, int y, int w, int h) {
	_rect = { x, y, w, h };
	SDL_Rect tmpRect = { _rect.x, _rect.y + 30, _rect.w, _rect.h };
	_rects[0] = tmpRect;
	_rects[1] = _rects[0];
	_rects[1].y = _rect.y + (int)(1.5*_rect.h);
	_rects[2] = tmpRect;
	_rects[2].y = _rect.y + (int)(2.8*_rect.h);
}

void ScreenShots::push() {
	Uint32 pFormat = SDL_PIXELFORMAT_RGB888;
	SDL_Surface *_tmp = SDL_CreateRGBSurfaceWithFormat(NULL, mainScreenWidth, mainScreenHeight, 32,
		pFormat);
	if (!_tmp) {
		SDL_FreeSurface(_tmp);
		return;
	}
	int res = SDL_RenderReadPixels(renderer, &screenShotRect, pFormat, _tmp->pixels,
		_tmp->pitch);
	std::string fName = "_SS";
	fName += std::to_string(screenShots.size());
	fName += ".jpg";
	SDL_SaveBMP(_tmp, fName.c_str());
	SDL_FreeSurface(_tmp);

	SDL_Surface *tmpSurface = IMG_Load(fName.c_str());
	SDL_Texture *tmpTexture = SDL_CreateTextureFromSurface(renderer, tmpSurface);
	SDL_FreeSurface(tmpSurface);
	
	screenShots.push_back(tmpTexture);
}

void ScreenShots::drawBorderRect(int x, int y, int w, int h) {
	SDL_Color tmpColor = { 0,0,0,255 };
	int pad = 3;
	mainScreen.drawRect(x, y, w, pad, tmpColor);
	mainScreen.drawRect(x , y + h, w, pad, tmpColor);
	mainScreen.drawRect(x, y, pad, h, tmpColor);
	mainScreen.drawRect(x + w, y, pad, h + pad, tmpColor);
}

void ScreenShots::setRenderer(SDL_Renderer *_r) {
	renderer = _r;
}

void ScreenShots::render(ScrollBar& _sc) {
	if (screenShots.size() == 0)
		return;

	calculateIndices();
	bulkIndex = _sc.currentLevel;

	if (bulkIndex < 1)
		return;

	if (extraLoops > 0 && bulkIndex == maxBulkIndex) {
		int j = 0;
		int i = 0;
		int start = 0;
		int end = 0;
		if (minLoops == 0) {
			start = 0;
			end = extraLoops;
		}
		else {
			start = (maxBulkIndex - 1) * 3;
			end = start + extraLoops;
		}
		for (int i = start; i < end; i++) {
			SDL_RenderCopy(mainScreen.getRenderer(), screenShots[i], &srcScreenShotRect, &_rects[j]);
			drawBorderRect(_rects[j].x - 10, _rects[j].y - 10, _rects[j].w + 10, _rects[j].h + 10);
			j++;
		}
	}
	else {
		int start = (bulkIndex - 1) * 3;
		int end = start + 3;
		int j = 0;
		for (int i = start; i < end; i++) {
			SDL_RenderCopy(mainScreen.getRenderer(), screenShots[i], &srcScreenShotRect, &_rects[j]);
			drawBorderRect(_rects[j].x - 10, _rects[j].y - 10, _rects[j].w + 10, _rects[j].h + 10);
			j++;
		}
	}
}

void ScreenShots::inc() {
	if (bulkIndex < maxBulkIndex)
		bulkIndex++;
}

void ScreenShots::dec() {
	if (bulkIndex > 1)
		bulkIndex--;
}

void ScreenShots::calculateIndices() {
	int _size = screenShots.size();
	maxBulkIndex = (_size / 3) + ((_size % 3) != 0);
	minLoops = _size / 3;
	extraLoops = _size % 3;
}

void ScreenShots::setInitialBulkIndex() {
	if (screenShots.size() > 0)
		bulkIndex = 1;
}

void ScreenShots::destroy() {
	for (unsigned long i = 0; i < screenShots.size(); i++) {
		SDL_DestroyTexture(screenShots[i]);
	}
	maxBulkIndex = { -1 };
	bulkIndex = { -1 };
	minLoops = { -1 };
	extraLoops = { -1 };
	currentImage = { -1 };
}

void ScreenShots::setCurrentImage() {
	int x = 0, y = 0;
	for (int i = 0; i < 3; i++) {
		if (event.type == SDL_MOUSEBUTTONDOWN) {
			SDL_GetMouseState(&x, &y);
			if (isMouseOn(_rects[i], x, y)) {
				currentImage = ((bulkIndex - 1) * 3) + i;
				updateSlide();
			}
		}
	}
}

void ScreenShots::updateSlide() {
	if (currentImage != -1) {
		int _tmpId = getIdFromSlide(sl.fileName, currentImage + 1);
		sl.setCurrentId(_tmpId);
		currentSlide = sl.getCurrentSlide();
	}
}

bool isMouseOn(SDL_Rect& _r, int x, int y) {
	if (x > _r.x && x < _r.x + _r.w
		&& y > _r.y && y < _r.y + _r.h)
		return true;
	return false;
}