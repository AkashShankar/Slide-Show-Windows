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
	/*
	try {
		
	}
	*/

	initAllApi();
	initBothScreens();
	initUI();
	initOthersHere();
	loop(events, mainScreenRender, inputScreenRender, quit, updateOthers);

	/*
	catch (const char* msg) {
		std::cout << msg << std::endl;
	}
	*/
	
	destroyBothScreens();
	closeAllApi();
	return 0;
}

void updateOthers() {
	//mySlide1.update();
	sl.updateSlide();
}

void initOthersHere() {
	//mySlide1.loadSlide(1, "fileHandle.txt", mainScreen.getRenderer());
	sl.setFile("fileHandle.txt");
	sl.setCurrentId(10);
	sl.loadSlide();
	currentSlide = sl.getCurrentSlide();
}

void mainScreenRender() {
	mainScreen.clearScreen();
	renderMainUI();
	//mySlide1.renderSlide();
	sl.renderSlide();
}

void inputScreenRender() {
	renderInputUI();
}

void events() {
	//mySlide1.process();
	
	sl.processSlide();

	processSaveButton(currentSlide);
	processMainUI();
	processInputUI();
}

void quit() {
	//mySlide1.destroy();
	sl.destroySlide();
	destroyUI();
}