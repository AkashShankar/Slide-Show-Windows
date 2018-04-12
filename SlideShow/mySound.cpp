#include "stdafx.h"
#include <iostream>
#include "mySound.h"
#include "utilities.h"
#include "fileHandle.h"

extern Screen mainScreen;
extern const Uint8* keyState;

void MySound::setInfo(std::vector<std::string> sl) {
    if(sl[0] == "Sound") {
		_vec = sl;
		current = getStringFromVector(_vec);
		text = sl[1].substr(5, sl[1].length() - 5);
        this->x = stoi(sl[2].substr(2, sl[2].length() - 2));
        this->y = stoi(sl[3].substr(2, sl[3].length() - 2));
        this->path = sl[4].substr(5, sl[4].length() - 5);
        sound.setPath(this->path);
        sound.init();
        initButton();
        button.initText(text, this->x, this->y);
    }
    else if(sl[0] == "Image" || sl[0] == "Text") {
        std::cout << sl[0] << " is not a Sound." << std::endl;
    }
    else {
        std::cout << "Unknown type: " << sl[0] << std::endl;
    }
}

std::vector<std::string> MySound::getUpdatedVector() {
	std::string _tmp;
	_tmp = "x:";
	_tmp += std::to_string(button.textRect.x);
	_vec.erase(_vec.begin() + 2);
	_vec.insert(_vec.begin() + 2, _tmp);

	_tmp = "y:";
	_tmp += std::to_string(button.textRect.y);
	_vec.erase(_vec.begin() + 3);
	_vec.insert(_vec.begin() + 3, _tmp);

	button.adjustPosition();

	return _vec;
}

void MySound::save(std::string fileName) {
	std::vector<std::string> _tmpVec = getUpdatedVector();
	std::string _tmpStr = getStringFromVector(_tmpVec);
	int line = getLineWhichContains(fileName, current);
	replaceLine(fileName, _tmpStr, line);
	current = _tmpStr;
}

void MySound::checkAndDelete(std::string fName) {
	if (keyState[SDL_SCANCODE_X]) {
		int _line = getLineWhichContains(fName, current);
		if (_line != -1)
			deleteLineInFile(fName, _line);
	}
}

void MySound::checkToPlay() {
	static bool test = false;
	if (getClicked() != test) {
		std::string _t = text;
		if (!Mix_PlayingMusic())
			playMusic = true;
		else if (Mix_PausedMusic()) {
			Mix_ResumeMusic();
			resumedMusic = true;
		}
		else {
			Mix_PauseMusic();
			playMusic = false;
			resumedMusic = false;
		}
		test = getClicked();
		if (playMusic || resumedMusic)
			_t += ": Pause";
		else
			_t += ": Play";
		button.reInitText(_t.c_str(), button.textRect.x, button.textRect.y);
	}
	if (playMusic) {
		Mix_PlayMusic(sound.get_music(), 1);
	}
}

bool MySound::getClicked() {
    return button.clickedToAction;
}

void MySound::initButton() {
    button.init("TNR.ttf", 20, 7, 7);
    button.initFont();
    button.setRenderer(mainScreen.getRenderer());
    button.setColors(RED, BLUE, BLACK, WHITE);
}

void MySound::renderButton() {
    button.drawButton(mainScreen);
}

void MySound::destroy() {
    sound.destroy();
    button.destroy();
	button.action1 = nullptr;
	button.action2 = nullptr;
	button.buttonRect = { 0,0,0,0 };
	button.textRect = { 0,0,0,0 };
}

void MySound::processButton() {
	button.process();
    button.checkBounds1();
}

void MySound::processSound() {
	checkToPlay();
}