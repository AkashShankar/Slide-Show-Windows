#include "stdafx.h"
#include <iostream>
#include "mySound.h"
using namespace std;

extern Screen mainScreen;
void actionFunc(Button &b);

void MySound::setInfo(std::vector<std::string> sl) {
    if(sl[0] == "Sound") {
        this->sTime = stoi(sl[1].substr(2, sl[1].length() - 2));
        this->rTime = stoi(sl[2].substr(2, sl[2].length() - 2));
        string tmp = sl[3].substr(5, sl[3].length() - 5);
        this->x = stoi(sl[4].substr(2, sl[4].length() - 2));
        this->y = stoi(sl[5].substr(2, sl[5].length() - 2));
        this->path = sl[6].substr(5, sl[6].length() - 5);
        sound.setPath(this->path);
        sound.init();
        sound.setStartTime(this->sTime);
        sound.setResetTime(this->rTime);
        initButton();
        button.initText(tmp, this->x, this->y);
    }
    else if(sl[0] == "Image" || sl[0] == "Text") {
        cout << sl[0] << " is not a Sound." << endl;
    }
    else {
        cout << "Unknown type: " << sl[0] << endl;
    }
}

/*
void MySound::buttonAction() {
    clicked = !clicked;
    if(clicked) {
        sound.timer.hasStarted = true;
    }
    else {
        sound.timer.hasStarted = false;
    }
}
 */

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
}

void MySound::processButton() {
    button.checkAndTakeAction();
    button.process();
    button.checkBounds1();
}

void MySound::processSound() {
    sound.start();
    sound.process();
}
