#pragma once
#include <SDL.h>
#include <string>
#include <vector>
#include "Image.h"

std::string getStringFromVector(std::vector<std::string> _t);

enum Resource{
    TEXT , IMAGE , SOUND
};

enum Color{
    RED, BLUE, GREEN, YELLOW, BLACK, WHITE,
    GRAY, LBLUE, DPINK, LPINK, MAGENTA, DGREEN,
    OLIVE, MAROON, PURPLE, TEAL, NAVY
};

class Timer {
private:
    double timeElapsed = 0.0;
    double toStart = 0.0;
    double resetTime = 0.0;
public:
    bool hasStarted = false;
    void startClock();
    void setResetTime(double r);
    void setStartTime(double s);
};

class ScrollBar {
private:
	SDL_Rect _rect;
	SDL_Color _c;
	bool clicked = false;
	int upperBoundY = 0;
	int lowerBoundY = 0;
public:
	void set(int x, int y, int w, int h);
	void setColor(Color c);
	void setBounds(int upper, int lower);
	void draw();
	void checkAndMove();
	bool isMouseOnRect(int x, int y);
	void adjustRect();
};

class ScreenShots {
private:
	std::vector<SDL_Texture*> screenShots;
	SDL_Renderer *renderer{ nullptr };
	SDL_Rect _rect;
public:
	ScreenShots();
	void setRenderer(SDL_Renderer *_r);
	void push();
	void set(int x, int y, int w, int h);
	void render();
	void drawBorderRect(int x, int y, int w, int h);
};

void setColor(SDL_Color &color, Color c);
SDL_Color getColorFromPixel(Uint32 number);
void putColorToPixel(Uint32 &number, SDL_Color color);
double map(double from, double fromRange, double toRange);
Color getColorFromString(std::string c);
bool checkIfNum(std::string _str);
