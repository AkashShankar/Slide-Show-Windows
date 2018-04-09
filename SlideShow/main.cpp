#include "stdafx.h"
#include <iostream>
#include "initApi.h"
#include "screen.h"
#include "handle.h"
#include "mySlide.h"
#include "ui.h"
#include "fileHandle.h"
#include "utilities.h"
#include "SlideShow.h"
#include "SlideId.h"
#include "TextInput.h"

const char* inputProcessError = "Could not process input";

/* Both Screens */
extern Screen mainScreen;
extern Screen inputScreen;
extern SDL_Event event;
extern Image nextButton;
extern Image backButton;
extern Button saveButton;
extern Button refreshButton;
extern const Uint8* keyState;
/* Both Screens */

/* Mandatory Functions */
void mainScreenRender();
void inputScreenRender();
void events();
void quit();
void initOthersHere();
void updateOthers();
void nextSlide();
void previousSlide();
void loadAllSlides();
int getIndexWithId(int id);
void save(MySlide& _s);
void refresh();
void processInput();
/* Mandatory Functions */

/* Global variables */
MySlide currentSlide;
SlideShow sl;
SlideId slideId;
TextInput txtInput("courbd.ttf", YELLOW);
/* Global variables */

int main(int argc, char * argv[]) {
	try {
		initAllApi();
		initBothScreens();
		initUI();
		initOthersHere();
		loop(events, mainScreenRender, inputScreenRender, quit, updateOthers);
	}
	catch (const char* msg) {
		std::cout << msg << std::endl;
	}
	destroyBothScreens();
	closeAllApi();
	system("pause");
	return 0;
}

void updateOthers() {
	currentSlide.update();
}

void initOthersHere() {
	inputScreen.hide();

	sl.setFile("fileHandle.txt");
	
	slideId.setFile(sl.fileName);
	loadAllSlides();

	nextButton.action = nextSlide;
	backButton.action = previousSlide;
	refreshButton.action1 = refresh;
	saveButton.action2 = save;

	txtInput.setPos(80, 10);
	txtInput.init();
}

void mainScreenRender() {
	mainScreen.clearScreen();
	renderMainUI();
	currentSlide.renderSlide();
}

void inputScreenRender() {
	renderInputUI();
	txtInput.render();
}

void events() {
	currentSlide.process();
	processSaveButton(currentSlide);
	processNewImageButton(currentSlide);
	processNewTextButton(currentSlide);
	processNewSoundButton(currentSlide);
	processMainUI();
	processInputUI();
	if(inputScreen.keyboardFocus)
		txtInput.textLoop();
}

void quit() {
	currentSlide.destroy();
	std::cout << "------------------" << std::endl;
	destroyUI();
	txtInput.destroy();
}

void nextSlide() {
	slideId.increment();
	sl.setCurrentId(slideId.currentId);
	currentSlide = sl.getCurrentSlide();
}

void previousSlide() {
	slideId.decrement();
	sl.setCurrentId(slideId.currentId);
	currentSlide = sl.getCurrentSlide();
}

void loadAllSlides() {
	
	slideId.currentIndex = -1;
	slideId._ids.erase(slideId._ids.begin(), slideId._ids.end());
	slideId.loadAllIds();
	int numSlides = slideId.getNumIds();
	for (int i = 0; i < numSlides; i++) {
		slideId.increment();
		sl.setCurrentId(slideId.currentId);
		sl.loadSlide();
	}
	if (numSlides >= 1) {
		slideId.currentIndex = 0;
		slideId.currentId = slideId._ids[0];
		sl.setCurrentId(slideId.currentId);
		currentSlide = sl.getCurrentSlide();
	}
}

int getIndexWithId(int id) {
	int si = slideId.getNumIds();
	for (int i = 0; i < si; i++) {
		if (slideId._ids[i] == id)
			return i;
	}
	return -1;
}

void save(MySlide& _s) {
	_s.save(_s.fileName);
	std::cout << "Slide with id: " << _s.id << " saved" << std::endl;
}

void refresh() {
	sl._slides.erase(sl._slides.begin(), sl._slides.end());
	loadAllSlides();
}

void processInput() {
	std::string _tmp;
	_tmp = txtInput.get();
	std::vector<std::string> _tmpVec;
	split(_tmp, _tmpVec);
	std::string finalString;
	std::vector<std::string> finalVec;
	std::vector<std::string> testVec;
	splitString(_tmpVec[0], testVec, ' ');

	try {
		if (testVec[0] == "Text") {
			if(testVec.size() != 3)
				throw inputProcessError;
			splitString(_tmpVec[0], finalVec, ' ');
			finalVec.push_back(_tmpVec[1]);
			if (finalVec.size() != 4)
				throw inputProcessError;
			finalVec[2] = finalVec[2].substr(0, finalVec[2].length() - 1);
			finalVec[3].insert(finalVec[3].begin(), '\"');
			finalVec[3].insert(finalVec[3].end(), '\"');
		}
		else if (testVec[0] == "Sound") {
			if (testVec.size() != 3)
				throw inputProcessError;
			splitString(_tmpVec[0], finalVec, ' ');
		}
		else if(testVec[0] == "Image") {
			if (testVec.size() != 2)
				throw inputProcessError;
			splitString(_tmpVec[0], finalVec, ' ');
		}
	}

	catch (const char* msg) {
		std::cout << msg << std::endl;
		txtInput.erase();
		inputScreen.hide();
		txtInput.stop();
		return;
	}

	if (finalVec[0] == "Image" && finalVec.size() == 2 && Image::ifImageExists(finalVec[1])) {
		finalString += finalVec[0];
		finalString += " x:200 y:300 w:200 h:200 path:";
		finalString += finalVec[1];
		std::cout << "Inserted Image: " << finalVec[1] << " to slide " << currentSlide.id << std::endl;
		currentSlide.insert(finalString);
	}
	else if (finalVec[0] == "Text" && finalVec.size() == 4 && Text::ifTextExists(finalVec[1])) {
		finalString = finalVec[0];
		finalString += " x:200 y:300 fontsize:20";
		finalString += " font:";
		finalString += finalVec[1];
		finalString += " Color:";
		finalString += finalVec[2];
		finalString += " text:";
		finalString += finalVec[3];
		std::cout << "Inserted Text: " << finalVec[3] << std::endl;
		currentSlide.insert(finalString);
	}
	else if (finalVec[0] == "Sound" && finalVec.size() == 3 && Sound::ifSoundExists(finalVec[1])) {
		finalString = finalVec[0];
		finalString += " text:";
		finalString += finalVec[2];
		finalString += " x:400 y:400";
		finalString += " path:";
		finalString += finalVec[1];
		std::cout << finalString << std::endl;
		std::cout << "Inserted Sound: " << finalVec[1] << std::endl;
		currentSlide.insert(finalString);
	}
	else {
		std::cout << "Resource: \"" << finalVec[1] << "\" not found" << std::endl;
	}
	txtInput.erase();
	inputScreen.hide();
	txtInput.stop();
}