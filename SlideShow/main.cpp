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

/* Both Screens */
extern Screen mainScreen;
extern Screen inputScreen;
extern SDL_Event event;
/* Both Screens */

/* Mandatory Functions */
void mainScreenRender();
void inputScreenRender();
void events();
void quit();
void initOthersHere();
void updateOthers();
/* Mandatory Functions */

/* Global variables */
MySlide currentSlide;
SlideShow sl;
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
	return 0;
}

void updateOthers() {
	currentSlide.update();
}

void initOthersHere() {
	sl.setFile("fileHandle.txt");
	sl.setCurrentId(10);
	sl.loadSlide();
	currentSlide = sl.getCurrentSlide();
	
}

void mainScreenRender() {
	mainScreen.clearScreen();
	renderMainUI();
	currentSlide.renderSlide();
}

void inputScreenRender() {
	renderInputUI();
}

void events() {
	currentSlide.process();
	processSaveButton(currentSlide);
	processMainUI();
	processInputUI();
}

void quit() {
	currentSlide.destroy();
	destroyUI();
}