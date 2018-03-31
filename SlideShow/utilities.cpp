#include "stdafx.h"
#include <iostream>
#include <ctime>
#include "utilities.h"


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
