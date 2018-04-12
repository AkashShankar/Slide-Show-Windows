#include "stdafx.h"
#include <iostream>
#include "myImage.h"
#include "utilities.h"
#include "fileHandle.h"

extern const Uint8* keyState;

using namespace std;

void MyImage::setInfo(std::vector<std::string> sl) {
    if(sl[0] == "Image") {
		_vec = sl;
		current = getStringFromVector(_vec);
		this->resType = IMAGE;
        this->rect.x = stoi(sl[1].substr(2, sl[1].length() - 2));
        this->rect.y = stoi(sl[2].substr(2, sl[2].length() - 2));
        this->rect.w = stoi(sl[3].substr(2, sl[3].length() - 2));
        this->rect.h = stoi(sl[4].substr(2, sl[4].length() - 2));
        this->path = sl[5].substr(5, sl[5].length() - 5);
    }
    else if(sl[0] == "Text" || sl[0] == "Sound") {
        cout << sl[0] << "is not an Image" << endl;
    }
    else {
        cout << "Unknown type: " << sl[0] << endl;
    }
}

std::vector<std::string> MyImage::getUpdatedVector() {
	std::string _t1 = "x:";

	_t1 +=  to_string(image.desRect.x);
	_vec.erase(_vec.begin() + 1);
	_vec.insert(_vec.begin() + 1, _t1);
	
	_t1 = "y:";
	_t1 += to_string(image.desRect.y);
	_vec.erase(_vec.begin() + 2);
	_vec.insert(_vec.begin() + 2, _t1);

	_t1 = "w:";
	_t1 += to_string(image.desRect.w);
	_vec.erase(_vec.begin() + 3);
	_vec.insert(_vec.begin() + 3, _t1);

	_t1 = "h:";
	_t1 += to_string(image.desRect.h);
	_vec.erase(_vec.begin() + 4);
	_vec.insert(_vec.begin() + 4, _t1);
	
	return _vec;
}

void MyImage::save(std::string fileName) {
	std::vector<std::string> _tmpVec = getUpdatedVector();
	std::string _tmpStr = getStringFromVector(_tmpVec);
	int line = getLineWhichContains(fileName, current);
	replaceLine(fileName, _tmpStr, line);
	current = _tmpStr;
}

void MyImage::setTexture(SDL_Renderer *renderer) {
	image.setRenderer(renderer);
	image.setPath(this->path);
	image.setDesRect(rect.x, rect.y, rect.w, rect.h);
}

void MyImage::changeAlpha_MyImage(bool increase){
	image.changeAlpha_Image(increase);
}

bool MyImage::clicked() {
    return image.clicked;
}

void MyImage::destroy() {
	image.destroy();
}

void MyImage::checkAndMove(){
    image.checkAndMove();
}

void MyImage::displayInfo() {
    cout << "x: " << rect.x << endl;
    cout << "y: " << rect.y << endl;
    cout << "w: " << rect.w << endl;
    cout << "h: " << rect.h << endl;
    cout << "path: " << path << endl;
}

void MyImage::renderDes() {
	image.renderDes();
}

void MyImage::checkToDelete(std::string fName) {
	if (keyState[SDL_SCANCODE_X]) {
		int line = getLineWhichContains(fName, current);
		if (line != -1)
			deleteLineInFile(fName, line);
	}
}