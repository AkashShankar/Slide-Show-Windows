#include "stdafx.h"
#include <iostream>
#include "myImage.h"

using namespace std;

void MyImage::setInfo(std::vector<std::string> sl) {
    if(sl[0] == "Image") {
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

void MyImage::setTexture(SDL_Renderer *renderer) {
    setRenderer(renderer);
    setPath(this->path);
    setDesRect(rect.x, rect.y, rect.w, rect.h);
}

void MyImage::changeAlpha_MyImage(bool increase){
    changeAlpha_Image(increase);
}

bool MyImage::clicked() {
    return Image::clicked;
}

void MyImage::destroy() {
    Image::destroy();
}

void MyImage::checkAndMove(){
    Image::checkAndMove();
}

void MyImage::displayInfo() {
    cout << "x: " << rect.x << endl;
    cout << "y: " << rect.y << endl;
    cout << "w: " << rect.w << endl;
    cout << "h: " << rect.h << endl;
    cout << "path: " << path << endl;
}

void MyImage::renderDes() {
    Image::renderDes();
}
