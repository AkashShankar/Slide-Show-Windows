#pragma once
#include <SDL.h>
#include "text.h"

extern SDL_Event event;

class TextInput {
private:
	std::string text;
	Text _txt;
	int x_pos{ 0 };
	int y_pos{ 0 };
	SDL_Color rectColor;
public:
	TextInput(std::string path, Color _rectColor);
	inline void erase() { text = ""; }
	inline void set(std::string _t) { text = _t; }
	inline std::string get() { return text; }
	void init();
	void setPos(int x, int y);
	void start();
	void stop();
	void render();
	void destroy();
	void textLoop();
};