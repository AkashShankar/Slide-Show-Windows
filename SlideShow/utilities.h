#pragma once
#include <SDL.h>
#include <string>
#include <vector>

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

void setColor(SDL_Color &color, Color c);
SDL_Color getColorFromPixel(Uint32 number);
void putColorToPixel(Uint32 &number, SDL_Color color);
double map(double from, double fromRange, double toRange);
Color getColorFromString(std::string c); 
