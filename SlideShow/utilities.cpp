#include "stdafx.h"
#include <iostream>
#include <ctime>
#include "utilities.h"
#include "screen.h"

extern Screen mainScreen;
extern SDL_Event event;
SDL_Rect screenShotRect;
SDL_Rect srcScreenShotRect;

void Timer::startClock() {
    static clock_t startClock = clock();
    timeElapsed = ( clock() - startClock ) / (double)CLOCKS_PER_SEC;
    if(timeElapsed >= toStart && timeElapsed <= resetTime)
        hasStarted = true;
    else
        hasStarted = false;
    if(timeElapsed >= resetTime)
        startClock = clock();
}

void Timer::setStartTime(double s) {
    toStart = s;
}

void Timer::setResetTime(double r) {
    resetTime = r;
}

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
	}
}

void ScrollBar::adjustRect() {
	if (_rect.y < upperBoundY)
		_rect.y = upperBoundY;
	else if (_rect.y > lowerBoundY)
		_rect.y = lowerBoundY;
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

void ScreenShots::render() {
	for (int i = 0; i < screenShots.size(); i++) {
		SDL_Rect tmpRect = { _rect.x, _rect.y + i * _rect.h, _rect.w, _rect.h };
		SDL_RenderCopy(mainScreen.getRenderer(), screenShots[i], &srcScreenShotRect, &tmpRect);
		drawBorderRect(_rect.x - 5, _rect.y + i * _rect.h, _rect.w + 10, _rect.h + 10);
	}
}