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

class ScreenShots;

class ScrollBar {
private:
	SDL_Rect _rect;
	SDL_Color _c;
	bool clicked = false;
	int upperBoundY = 0;
	int lowerBoundY = 0;
public:
	int totalLength{ 0 };
	int currentLength{ 0 };
	int maxLevels{ 0 };
	int currentLevel{ 0 };
public:
	void set(int x, int y, int w, int h);
	void setColor(Color c);
	void setBounds(int upper, int lower);
	void draw();
	void checkAndMove();
	bool isMouseOnRect(int x, int y);
	void adjustRect();
	void initalise(ScreenShots& _sc);
	void calculateCurrentLevel();
};

class ScreenShots {
private:
	std::vector<SDL_Texture*> screenShots;
	SDL_Renderer *renderer{ nullptr };
	SDL_Rect _rect;
public:
	SDL_Rect _rects[3];
	int minLoops{ -1 };
	int extraLoops{ -1 };
	int bulkIndex{ -1 };
	int maxBulkIndex{ -1 };
public:
	ScreenShots();
	void calculateIndices();
	void inc();
	void dec();
	void setRenderer(SDL_Renderer *_r);
	void push();
	void set(int x, int y, int w, int h);
	void render(ScrollBar& _sc);
	void drawBorderRect(int x, int y, int w, int h);
	void setInitialBulkIndex();
};

void setColor(SDL_Color &color, Color c);
SDL_Color getColorFromPixel(Uint32 number);
void putColorToPixel(Uint32 &number, SDL_Color color);
double map(double from, double fromRange, double toRange);
Color getColorFromString(std::string c);
bool checkIfNum(std::string _str);
