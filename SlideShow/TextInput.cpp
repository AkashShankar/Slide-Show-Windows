#include "stdafx.h"
#include "TextInput.h"
#include "screen.h"
#include <iostream>

extern Screen inputScreen;

TextInput::TextInput(std::string path, Color _rectColor) {
	_txt.setPath(path);
	_txt.setFontSize(20);
	_txt.setText("");
	_txt.setCol(BLACK);
	setColor(rectColor, _rectColor);
}

void TextInput::setPos(int x, int y) {
	x_pos = x;
	y_pos = y;
}

void TextInput::init() {
	_txt.setRenderer(inputScreen.getRenderer());
	_txt.setPos(x_pos, y_pos);
	_txt.init();
}

void TextInput::start() {
	SDL_StartTextInput();
}

void TextInput::stop() {
	SDL_StopTextInput();
}

void TextInput::render() {
	_txt.render();
}

void TextInput::destroy() {
	_txt.destroy();
}

void TextInput::textLoop() {
	if (event.type == SDL_TEXTINPUT || event.type == SDL_KEYDOWN) {
		if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_BACKSPACE
			&& text.length() > 0)
			text = text.substr(0, text.length() - 1);
		else if (event.key.keysym.sym == SDLK_RETURN)
			stop();
		else if (event.type == SDL_TEXTINPUT)
			text += event.text.text;
		_txt.setText(text);
		_txt.reinit();
	}
	inputScreen.drawRect(x_pos, y_pos, 300, 20, rectColor);
}
