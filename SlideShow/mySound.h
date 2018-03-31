#pragma once
#include <string>
#include <vector>
#include "Sound.h"
#include "button.h"

class MySound {
private:
    Button button;
    Resource resType = SOUND;
    std::string path;
    double sTime = 0.0;
    double rTime = 0.0;
    int x  = 400;
    int y = 400;
public:
    Sound sound;
public:
    void setInfo(std::vector<std::string> sl);
    void initButton();
    void renderButton();
    void buttonAction();
    void destroy();
    void processSound();
    void processButton();
    bool getClicked();
};
