#include "stdafx.h"
#include <SDL.h>
#include <iostream>
#include "ui.h"
#include "screen.h"
#include "button.h"
using namespace std;

/* External Variables */
extern Screen mainScreen;
extern Screen inputScreen;
extern bool isRunning;
/* External Variables */

/* Global Variables */
SDL_Rect upperBorder;
SDL_Rect leftBorder;
int paddingX = 6 , paddingY = 5 , buttonFontSize = 20;
string buttonFontPath = "TNR_Bold.ttf";
Color defHCol = BLUE , defBCol = BLACK , defICol = TEAL , defFCol = YELLOW;
Button exitButton(buttonFontPath, buttonFontSize, paddingX, paddingY);
Button openButton(buttonFontPath, buttonFontSize, paddingX, paddingY);
Button closeButton(buttonFontPath, buttonFontSize, paddingX, paddingY);
Button saveButton(buttonFontPath, buttonFontSize, paddingX, paddingY);
Button newSlideButton(buttonFontPath, buttonFontSize, paddingX, paddingY);
Button newImageButton(buttonFontPath, buttonFontSize, paddingX, paddingY);
Button newTextButton(buttonFontPath, buttonFontSize, paddingX, paddingX);
Button newSoundButton(buttonFontPath, buttonFontSize, paddingX, paddingY);
Button inputCloseButton(buttonFontPath, buttonFontSize, paddingX, paddingY);
/* Global Variables */

/* Declaration */
void setUpperBorder(int x, int y, int w, int h);
void drawUpperBorder(Color c);
void initUpperBorder();
void setLeftBorder(int x, int y, int w, int h);
void drawLeftBorder(Color c);
void initLeftBorder();
void setExitButton(int x, int y);
void setOpenButton(int x, int y);
void setCloseButton(int x, int y);
void setSaveButton(int x, int y);
void setNewSlideButton(int x, int y);
void setNewImageButton(int x, int y);
void setNewTextButton(int x, int y);
void setNewSoundButton(int x, int y);
void setInputCloseButton(int x, int y);
/* Declaration */

void save(MySlide& _s);
void exit();

void initOthers();

void setActionsForAll() {
	saveButton.action2 = save;
	exitButton.action1 = exit;
}

void save(MySlide& _s) {
	_s.save(_s.fileName);
	std::cout << "fileName: " << _s.fileName << std::endl;
	std::cout << "Saved slide with id: " << _s.id << std::endl;
}

void exit() {
	isRunning = false;
}

void processSaveButton(MySlide& _s) {
	saveButton.process(_s);
}
 
void initOthers() {
	setActionsForAll();
}

/* -------------UI Functions -------------*/
void initUI(){
    initUpperBorder();
    initLeftBorder();
    setExitButton(1220, 20);
    setOpenButton(30, 20);
    setCloseButton(120, 20);
    setSaveButton(210, 20);
    setNewSlideButton(330, 20);
    setNewImageButton(470, 20);
    setNewTextButton(630, 20);
    setNewSoundButton(770, 20);
    setInputCloseButton(30, 20);
	initOthers();
}

void processMainUI() {
    if(mainScreen.keyboardFocus) {
        exitButton.process();
        openButton.process();
        closeButton.process();
        //saveButton.process();
        newSlideButton.process();
        newImageButton.process();
        newTextButton.process();
        newSoundButton.process();
    }
}

void renderMainUI() {
    drawUpperBorder(DGREEN);
    drawLeftBorder(DGREEN);
    exitButton.drawButton(mainScreen);
    openButton.drawButton(mainScreen);
    closeButton.drawButton(mainScreen);
    saveButton.drawButton(mainScreen);
    newSlideButton.drawButton(mainScreen);
    newImageButton.drawButton(mainScreen);
    newTextButton.drawButton(mainScreen);
    newSoundButton.drawButton(mainScreen);
}

void renderInputUI() {
    inputCloseButton.drawButton(inputScreen);
}

void processInputUI() {
    inputCloseButton.process();
}

void destroyUI() {
    exitButton.destroy();
    openButton.destroy();
    closeButton.destroy();
    saveButton.destroy();
    newSlideButton.destroy();
    newImageButton.destroy();
    newTextButton.destroy();
    newSoundButton.destroy();
    inputCloseButton.destroy();
    cout << "All UI Destroyed" << endl;
}
/* -------------UI Functions -------------*/

void setUpperBorder(int x, int y, int w, int h){
    upperBorder = {x, y, w, h};
}

void drawUpperBorder(Color c){
    SDL_Color tmp;
    setColor(tmp, c);
    mainScreen.drawRect(upperBorder.x, upperBorder.y, upperBorder.w, upperBorder.h, tmp);
}

void setLeftBorder(int x, int y, int w, int h){
    leftBorder = {x, y, w, h};
}

void drawLeftBorder(Color c){
    SDL_Color tmp;
    setColor(tmp, c);
    mainScreen.drawRect(leftBorder.x, leftBorder.y, leftBorder.w, leftBorder.h, tmp);
}

void initLeftBorder(){
    setLeftBorder(300, 0, 3, mainScreenHeight);
    drawLeftBorder(BLACK);
}

void initUpperBorder(){
    setUpperBorder(0, 100, mainScreenWidth, 3);
    drawUpperBorder(BLACK);
}

void setExitButton(int x, int y) {
    exitButton.initFont();
    exitButton.setRenderer(mainScreen.getRenderer());
    exitButton.setColors(defBCol, RED, defICol, defFCol);
    exitButton.initText("Exit", x, y);
}

void setOpenButton(int x, int y) {
    openButton.initFont();
    openButton.setRenderer(mainScreen.getRenderer());
    openButton.setColors(defBCol, defHCol, defICol, defFCol);
    openButton.initText("Open", x, y);
}

void setCloseButton(int x, int y) {
    closeButton.initFont();
    closeButton.setRenderer(mainScreen.getRenderer());
    closeButton.setColors(defBCol, RED, defICol, defFCol);
    closeButton.initText("Close", x, y);
}

void setSaveButton(int x, int y) {
    saveButton.initFont();
    saveButton.setRenderer(mainScreen.getRenderer());
    saveButton.setColors(defBCol, defHCol, defICol, defFCol);
    saveButton.initText("Save", x, y);
}

void setNewSlideButton(int x, int y) {
    newSlideButton.initFont();
    newSlideButton.setRenderer(mainScreen.getRenderer());
    newSlideButton.setColors(defBCol, defHCol, defICol, defFCol);
    newSlideButton.initText("New Slide", x, y);
}

void setNewImageButton(int x, int y) {
    newImageButton.initFont();
    newImageButton.setRenderer(mainScreen.getRenderer());
    newImageButton.setColors(defBCol, defHCol, defICol, defFCol);
    newImageButton.initText("New Image", x, y);
}

void setNewTextButton(int x, int y) {
    newTextButton.initFont();
    newTextButton.setRenderer(mainScreen.getRenderer());
    newTextButton.setColors(defBCol, defHCol, defICol, defFCol);
    newTextButton.initText("New Text", x, y);
}

void setNewSoundButton(int x, int y) {
    newSoundButton.initFont();
    newSoundButton.setRenderer(mainScreen.getRenderer());
    newSoundButton.setColors(defBCol, defHCol, defICol, defFCol);
    newSoundButton.initText("New Sound", x, y);
}

void setInputCloseButton(int x, int y) {
    inputCloseButton.initFont();
    inputCloseButton.setRenderer(inputScreen.getRenderer());
    inputCloseButton.setColors(defBCol, defHCol, defICol, defFCol);
    inputCloseButton.initText("Close", x, y);
}
