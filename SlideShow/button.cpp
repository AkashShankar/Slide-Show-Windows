#include "stdafx.h"
#include <iostream>
#include "button.h"

extern SDL_Event event;
extern SDL_Rect upperBorder;
extern SDL_Rect leftBorder;
extern const Uint8* keyState;

Button::Button(std::string fontPath, int fontSize, int xPad, int yPad){
    renderer = nullptr; texture = nullptr;
    font = nullptr; action1 = nullptr;
    this->fontPath = fontPath;
    this->fontSize = fontSize;
    this->xPad = xPad;
    this->yPad = yPad;
}

void Button::setRenderer(SDL_Renderer *renderer){
    this->renderer = renderer;
}

Button::Button() {
    renderer = nullptr; texture = nullptr;
    font = nullptr; action1 = nullptr;
}

void Button::init(std::string fontPath, int fontSize, int xPad, int yPad) {
    this->fontPath = fontPath;
    this->fontSize = fontSize;
    this->xPad = xPad;
    this->yPad = yPad;
}

void Button::initFont(){
    font = TTF_OpenFont(fontPath.c_str(), fontSize);
    if( !font ){
        std::cout << "Could not open font: " << TTF_GetError() << std::endl;
        return;
    }
}

void Button::initText(std::string text, int x, int y){
    this->text = text;
    SDL_Surface *tmp = TTF_RenderText_Solid(font, text.c_str(), fontCol);
    texture = SDL_CreateTextureFromSurface(renderer, tmp);
    SDL_FreeSurface(tmp);
    setTextRect(x, y);
    adjustPosition();
}

void Button::reInitText(std::string text, int x, int y) {
	if (texture != nullptr)
		SDL_DestroyTexture(texture);
	initText(text, x, y);
}

void Button::setTextRect(int x, int y){
    this->textRect.x = x;
    this->textRect.y = y;
    SDL_QueryTexture(texture, NULL, NULL, &textRect.w, &textRect.h);
}

void Button::adjustPosition(){
    buttonRect.x = textRect.x - xPad;
    buttonRect.y = textRect.y - yPad;
    buttonRect.w = textRect.w + xPad * 2;
    buttonRect.h =  textRect.h + yPad * 2;
}

void Button::drawRect(Screen &sc){
    int xFrom = buttonRect.x;
    int xTo = xFrom +  buttonRect.w;
    int yFrom = buttonRect.y;
    int yTo = yFrom + buttonRect.h;
    for(int i=xFrom;i<xTo;i++){
        for(int j=yFrom;j<yTo;j++){
            if(j < yFrom + 3 || j > yTo - 2 ||
               i < xFrom + 3 || i > xTo - 2)
                sc.setPixel(i, j, borderCol);
            else
                sc.setPixel(i, j, currentCol);
        }
    }
}

void Button::setColors(Color bCol, Color hCol, Color iColor, Color fCol){
    setColor(borderCol, bCol);
    setColor(highlightCol, hCol);
    setColor(insideCol, iColor);
    setColor(fontCol, fCol);
}

void Button::render(){
    SDL_RenderCopy(renderer, texture, NULL, &textRect);
}

void Button::checkAndTakeAction(){
    int x  = 0, y = 0;
    //clickedToAction = false; // Do not uncomment this
    if(event.type == SDL_MOUSEMOTION || event.type == SDL_MOUSEBUTTONDOWN
       || event.type == SDL_MOUSEBUTTONUP ){
        SDL_GetMouseState(&x, &y);
        if(event.type == SDL_MOUSEBUTTONDOWN) {
            if(isMouseOnButton(x, y)){
                if(event.button.button == SDL_BUTTON_LEFT) {
                    if(action1 != nullptr)
                        action1();
                    clickedToMove = true;
                    clickedToAction = !clickedToAction;
                }
            }
        }
        if(event.type == SDL_MOUSEBUTTONUP) {
            clickedToMove = false;
        }
        if(clickedToMove && keyState[SDL_SCANCODE_SPACE]) {
            textRect.x = x;
            textRect.y = y;
            clickedToAction = false;
            adjustPosition();
        }
    }
}


void Button::checkBounds1() {
    if(textRect.y < upperBorder.y + 10 || textRect.x < leftBorder.x + 10) {
        textRect.x += 10;
        textRect.y += 10;
        adjustPosition();
    }
}

void Button::process() {
    checkAndTakeAction();
    highLightButton();
}

void Button::highLightButton() {
    if(event.type == SDL_MOUSEMOTION || event.type == SDL_MOUSEBUTTONDOWN) {
        int x , y;
        SDL_GetMouseState(&x, &y);
        if(isMouseOnButton(x, y)) {
            currentCol = highlightCol;
        }else {
            currentCol = insideCol;
        }
    }
}

bool Button::isMouseOnButton(int x, int y){
    if(x > buttonRect.x && x < buttonRect.x + buttonRect.w
       && y > buttonRect.y && y < buttonRect.y + buttonRect.h)
        return true;
    return false;
}

void Button::drawButton(Screen sc){
    drawRect(sc);
    render();
}

void Button::destroy(){
    if(renderer != nullptr)
        SDL_DestroyRenderer(renderer);
    if(texture != nullptr)
        SDL_DestroyTexture(texture);
    if(font != nullptr)
        TTF_CloseFont(font);
}

