#pragma once
#include <string>
#include <vector>
#include "Sound.h"
#include "button.h"

class MySound {
private:
    Resource resType = SOUND;
    std::string path;
    int x  = 400;
    int y = 400;
	std::vector<std::string> _vec;
public:
	Button button;
	std::string current;
	std::string text;
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
	std::vector<std::string> getUpdatedVector();
	void save(std::string fileName);
	void checkAndDelete(std::string fName);
};
