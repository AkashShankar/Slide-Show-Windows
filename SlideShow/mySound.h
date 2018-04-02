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
    int x  = 400;
    int y = 400;
public:
    Sound sound;
	bool playMusic = false;
	bool resumedMusic = false;
public:
    void setInfo(std::vector<std::string> sl);
    void initButton();
    void renderButton();
	void checkToPlay();
    void destroy();
    void processSound();
    void processButton();
    bool getClicked();
};
