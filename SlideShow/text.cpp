#include "stdafx.h"
#include <iostream>
#include "text.h"
using namespace std;

extern SDL_Event event;
extern SDL_Rect upperBorder;
extern SDL_Rect leftBorder;
extern const Uint8* keyState;

Text::Text(std::string fontPath, int fontSize) {
    this->fontPath = fontPath;
    this->fontSize = fontSize;
}

void Text::setRenderer(SDL_Renderer *renderer) {
    this->renderer = renderer;
}

void Text::setPos(int x, int y) {
    rect.x = x;
    rect.y = y;
}

void Text::setText(std::string text) {
    this->text = text;
}

void Text::setCol(Color c) {
    setColor(fontColor, c);
}

void Text::init() {
    font = TTF_OpenFont(fontPath.c_str(), fontSize);
    if(!font) {
        cout << "TTF Could not open font: " << TTF_GetError << endl;
        return;
    }
    SDL_Surface *tmpSurface = TTF_RenderText_Solid(font, text.c_str(), fontColor);
	if (!tmpSurface)
		return;
    texture = SDL_CreateTextureFromSurface(renderer, tmpSurface);
	if (!texture) {
		std::cout << "SDL: " << SDL_GetError() << std::endl;
		return;
	}
    SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
    SDL_FreeSurface(tmpSurface);
}

void Text::reinit() {
	if (font != nullptr)
		TTF_CloseFont(font);
	if (texture != nullptr)
		SDL_DestroyTexture(texture);
	font = TTF_OpenFont(fontPath.c_str(), fontSize);
	SDL_Surface *tmpSurface = TTF_RenderText_Solid(font, text.c_str(), fontColor);
	texture = SDL_CreateTextureFromSurface(renderer, tmpSurface);
	SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
	SDL_FreeSurface(tmpSurface);
}

void Text::render() {
    SDL_RenderCopy(renderer, texture, NULL, &rect);
}

void Text::checkAndMove() {
    int x, y;
    if(event.type == SDL_MOUSEMOTION || event.type == SDL_MOUSEBUTTONUP
       || event.type == SDL_MOUSEBUTTONDOWN) {
		SDL_GetMouseState(&x, &y);
        if(event.type == SDL_MOUSEBUTTONDOWN){
            if(isMouseOn(x, y)) {
                clicked = true;
            }
        }
        if(event.type == SDL_MOUSEBUTTONUP) {
            clicked = false;
        }
		if (clicked) {
			if (!keyState[SDL_SCANCODE_A] && !keyState[SDL_SCANCODE_D]) {
				rect.x = x;
				rect.y = y;
			}
			else if (keyState[SDL_SCANCODE_A]) {
				fontSize -= 1;
				reinit();
			}
			else {
				fontSize += 1;
				reinit();
			}
		}
    }
	
    adjustDesRect();
}

void Text::adjustDesRect(){
    if( rect.x < leftBorder.x ){
        rect.x = leftBorder.x + 10;
    }
    if( rect.y < upperBorder.y ){
        rect.y = upperBorder.y + 10;
    }
}

bool Text::isMouseOn(int x, int y) {
    if(x > rect.x && x < rect.x + rect.w
       && y > rect.y && y < rect.y + rect.h)
        return true;
    return false;
}

void Text::destroy() {
    if(font != nullptr)
        TTF_CloseFont(font);
    if(texture != nullptr)
        SDL_DestroyTexture(texture);
    if(renderer != nullptr)
        SDL_DestroyRenderer(renderer);
}
