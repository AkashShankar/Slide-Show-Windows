#pragma once
#include <vector>
#include "text.h"

class MyText {
private:
    Resource resType;
    int fontSize = 10;
    std::string fontPath;
    Color fontColor;
	std::vector<std::string> _vec;
public:
	Text text;
	std::string current;
public:
    void setInfo(std::vector<std::string> sl);
    void init(SDL_Renderer *renderer);
    void checkAndMove();
    void render();
    void destroy();
	void save(std::string fileName);
	std::vector<std::string> getUpdatedVector();
	std::string customGetStringFromVector(std::vector<std::string> &t);
};

