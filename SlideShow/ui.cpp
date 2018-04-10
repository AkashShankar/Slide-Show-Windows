#include "stdafx.h"
#include <SDL.h>
#include <iostream>
#include "ui.h"
#include "screen.h"
#include "button.h"
#include "TextInput.h"
#include "SlideShow.h"
#include "SlideId.h"
using namespace std;

/* External Variables */
extern Screen mainScreen;
extern Screen inputScreen;
extern bool isRunning;
extern TextInput txtInput;
extern void processInput();
extern SlideShow sl;
extern SlideId slideId;
/* External Variables */

/* Global Variables */
SDL_Rect upperBorder;
SDL_Rect leftBorder;
SDL_Rect bottomBorder;
SDL_Rect scrollBarBorder;
int paddingX = 6 , paddingY = 6 , buttonFontSize = 18;
string buttonFontPath = "courbd.ttf";
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
Button refreshButton(buttonFontPath, buttonFontSize, paddingX, paddingY);
Button inputEnterButton(buttonFontPath, buttonFontSize, paddingX, paddingY);

// Image Buttons
Image nextButton;
Image backButton;
Image playSlidesButton;

//Text
Text EnterText;
void initText();

int navigateButtonWidth = 55; // Keep it 55
int navigateButtonHeight = 55;
/* Global Variables */

/* Declaration */
void setUpperBorder(int x, int y, int w, int h);
void drawUpperBorder(Color c);
void initUpperBorder();
void setLeftBorder(int x, int y, int w, int h);
void drawLeftBorder(Color c);
void initLeftBorder();
void initBottomBorder();
void drawBottomBorder(Color c);
void setBottomBorder(int x, int y, int w, int h);
void setScrollBarBorder(int x, int y, int w, int h);
void drawScrollBarBorder(Color c);
void initScrollBarBorder();
void setExitButton(int x, int y);
void setOpenButton(int x, int y);
void setCloseButton(int x, int y);
void setSaveButton(int x, int y);
void setNewSlideButton(int x, int y);
void setNewImageButton(int x, int y);
void setNewTextButton(int x, int y);
void setNewSoundButton(int x, int y);
void setInputCloseButton(int x, int y);
void setRefreshButton(int x, int y);
void setInputEnterButton(int x, int y);

// Image Buttons
void initNextButton(int x, int y);
void initBackButton(int x, int y);
void initPlaySlidesButton(int x, int y);

void renderAllNavigationButtons();
void processAllNavigationButtons();
/* Declaration */

void exit();
void hideInputWindow();
void newImageFunction(MySlide& _s);
void newTextFunction(MySlide& _s);
void newSoundFunction(MySlide& _s);
void newSlideFunction();
void openButtonFunction();
void closeButtonFunction();
void okButton();
void initOthers();

void setActionsForAll() {
	exitButton.action1 = exit;
	inputCloseButton.action1 = hideInputWindow;
	newImageButton.action2 = newImageFunction;
	newTextButton.action2 = newTextFunction;
	newSoundButton.action2 = newSoundFunction;
	newSlideButton.action1 = newSlideFunction;
	openButton.action1 = openButtonFunction;
	closeButton.action1 = closeButtonFunction;
	inputEnterButton.action1 = okButton;
}

void newSlideFunction() {
	txtInput.erase();
	txtInput.set("id ");
	txtInput.start();
	inputScreen.show();
}

void newImageFunction(MySlide& _s) {
	txtInput.erase();
	txtInput.set("Image ");
	txtInput.start();
	inputScreen.show();
}

void openButtonFunction() {
	txtInput.erase();
	txtInput.set("filename ");
	txtInput.start();
	inputScreen.show();
}

void newTextFunction(MySlide& _s) {
	txtInput.erase();
	txtInput.set("Text ");
	txtInput.start();
	inputScreen.show();
}

void newSoundFunction(MySlide& _s) {
	txtInput.erase();
	txtInput.set("Sound ");
	txtInput.start();
	inputScreen.show();
}

void closeButtonFunction() {
	sl.destroySlide();
	sl.setFile("");
	slideId._ids.erase(slideId._ids.begin(), slideId._ids.end());
}

void okButton() {
	processInput();
}

void hideInputWindow() {
	txtInput.stop();
	txtInput.erase();
	SDL_HideWindow(inputScreen.getWindow());
}

void exit() {
	isRunning = false;
}

void processNewTextButton(MySlide& _s) {
	newTextButton.checkAndTakeAction(_s);
}

void processNewImageButton(MySlide& _s) {
	newImageButton.checkAndTakeAction(_s);
}

void processNewSoundButton(MySlide& _s) {
	newSoundButton.checkAndTakeAction(_s);
}

void processNewSlideButton() {
	newSlideButton.checkAndTakeAction();
}

void processSaveButton(MySlide& _s) {
	saveButton.process(_s);
}

void processOpenButton() {
	openButton.checkAndTakeAction();
}

void processCloseButton() {
	closeButton.checkAndTakeAction();
}

void initOthers() {
	setActionsForAll();
	initPlaySlidesButton(30, 740);
	initNextButton(200, 740);
	initBackButton(120, 740);
}

void renderAllNavigationButtons() {
	nextButton.renderDes();
	backButton.renderDes();
	playSlidesButton.renderDes();
}

void processAllNavigationButtons() {
	nextButton.checkToAction();
	backButton.checkToAction();
	playSlidesButton.checkToAction();
}

/* -------------UI Functions -------------*/
void initUI(){
    initUpperBorder();
    initLeftBorder();
	initBottomBorder();
	initScrollBarBorder();
    setExitButton(1220, 20);
    setOpenButton(30, 20);
    setCloseButton(110, 20);
    setSaveButton(200, 20);
    setNewSlideButton(330, 20);
    setNewImageButton(420, 20);
    setNewTextButton(510, 20);
    setNewSoundButton(590, 20);
	setRefreshButton(30, 65);

    setInputCloseButton(340, 65);
	setInputEnterButton(280, 65);
	initOthers();

	initText();
}

void processMainUI() {
    if(mainScreen.keyboardFocus) {
        exitButton.process();
        openButton.process();
        closeButton.process();
        newSlideButton.process();
        newImageButton.process();
        newTextButton.process();
        newSoundButton.process();
		refreshButton.process();
		processAllNavigationButtons();
		renderAllNavigationButtons();
    }
}

void renderMainUI() {
    drawUpperBorder(DGREEN);
    drawLeftBorder(DGREEN);
	drawBottomBorder(DGREEN);
	drawScrollBarBorder(DGREEN);
    exitButton.drawButton(mainScreen);
    openButton.drawButton(mainScreen);
    closeButton.drawButton(mainScreen);
    saveButton.drawButton(mainScreen);
    newSlideButton.drawButton(mainScreen);
    newImageButton.drawButton(mainScreen);
    newTextButton.drawButton(mainScreen);
    newSoundButton.drawButton(mainScreen);
	refreshButton.drawButton(mainScreen);
	renderAllNavigationButtons();
}

void renderInputUI() {
    inputCloseButton.drawButton(inputScreen);
	inputEnterButton.drawButton(inputScreen);
	EnterText.render();
}

void processInputUI() {
    inputCloseButton.process();
	inputEnterButton.process();
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
	refreshButton.destroy();
	inputEnterButton.destroy();
    cout << "All UI Destroyed" << endl;
}
/* -------------UI Functions -------------*/

void initBottomBorder() {
	setBottomBorder(0, 730, 300, 3);
	drawLeftBorder(BLACK);
}

void drawBottomBorder(Color c) {
	SDL_Color tmp;
	setColor(tmp, c);
	mainScreen.drawRect(bottomBorder.x, bottomBorder.y, bottomBorder.w, bottomBorder.h, tmp);
}

void setBottomBorder(int x, int y, int w, int h) {
	bottomBorder = { x, y, w, h };
}

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

void setScrollBarBorder(int x, int y, int w, int h) {
	scrollBarBorder = { x, y, w, h };
}

void drawScrollBarBorder(Color c) {
	SDL_Color tmp;
	setColor(tmp, c);
	mainScreen.drawRect(scrollBarBorder.x, scrollBarBorder.y, scrollBarBorder.w, scrollBarBorder.h, tmp);
}

void initScrollBarBorder() {
	setScrollBarBorder(272, 100, 3, 630);
	drawScrollBarBorder(BLACK);
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
    newSlideButton.initText("Slide", x, y);
}

void setNewImageButton(int x, int y) {
    newImageButton.initFont();
    newImageButton.setRenderer(mainScreen.getRenderer());
    newImageButton.setColors(defBCol, defHCol, defICol, defFCol);
    newImageButton.initText("Image", x, y);
}

void setNewTextButton(int x, int y) {
    newTextButton.initFont();
    newTextButton.setRenderer(mainScreen.getRenderer());
    newTextButton.setColors(defBCol, defHCol, defICol, defFCol);
    newTextButton.initText("Text", x, y);
}

void setNewSoundButton(int x, int y) {
    newSoundButton.initFont();
    newSoundButton.setRenderer(mainScreen.getRenderer());
    newSoundButton.setColors(defBCol, defHCol, defICol, defFCol);
    newSoundButton.initText("Sound", x, y);
}

void setInputCloseButton(int x, int y) {
    inputCloseButton.initFont();
    inputCloseButton.setRenderer(inputScreen.getRenderer());
    inputCloseButton.setColors(defBCol, defHCol, defICol, defFCol);
    inputCloseButton.initText("Close", x, y);
}

void setRefreshButton(int x, int y) {
	refreshButton.initFont();
	refreshButton.setRenderer(mainScreen.getRenderer());
	refreshButton.setColors(defBCol, defHCol, defICol, defFCol);
	refreshButton.initText("Refresh", x, y);
}

// Image Button

void initNextButton(int x, int y) {
	nextButton.setRenderer(mainScreen.getRenderer());
	nextButton.setPath("blackArrowRight.png");
	nextButton.setDesRect(x, y, navigateButtonWidth, navigateButtonHeight);
}

void initBackButton(int x, int y) {
	backButton.setRenderer(mainScreen.getRenderer());
	backButton.setPath("blackArrowLeft.png");
	backButton.setDesRect(x, y, navigateButtonWidth, navigateButtonHeight);
}

void initPlaySlidesButton(int x, int y) {
	playSlidesButton.setRenderer(mainScreen.getRenderer());
	playSlidesButton.setPath("play-sign.png");
	playSlidesButton.setDesRect(x, y, navigateButtonWidth, navigateButtonHeight);
}

void setInputEnterButton(int x, int y) {
	inputEnterButton.initFont();
	inputEnterButton.setRenderer(inputScreen.getRenderer());
	inputEnterButton.setColors(defBCol, defHCol, defICol, defFCol);
	inputEnterButton.initText("Ok", x, y);
}

void initText() {
	EnterText.setPath("TNR.ttf");
	EnterText.setFontSize(22);
	EnterText.setText("Enter: ");
	EnterText.setCol(BLACK);
	EnterText.setPos(10, 11);
	EnterText.setRenderer(inputScreen.getRenderer());
	EnterText.init();
}