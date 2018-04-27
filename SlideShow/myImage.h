#pragma once

#include <string>
#include <vector>
#include "Image.h"
#include "utilities.h"

class MyImage: public Image
{
private:
    SDL_Rect rect;
    Resource resType;
	std::vector<std::string> _vec;
public:
	std::string path;
	std::string current;
	//Image image;
public:
    void setInfo(std::vector<std::string> sl);
    void setTexture(SDL_Renderer *renderer);
    void checkAndMove();
    bool clicked();
    void changeAlpha_MyImage(bool increase);
    void displayInfo();
    void renderDes();
    void destroy();
	std::vector<std::string> getUpdatedVector();
	void save(std::string fileName);
	void checkToDelete(std::string fName);
};
