#include "stdafx.h"
#include <iostream>
#include "myText.h"
#include "fileHandle.h"
using namespace std;

void MyText::setInfo(vector<string> sl) {
    
    if(sl[0] == "Text") {
        resType = TEXT;
        int tmpX  = 0, tmpY = 0;
        tmpX = stoi(sl[1].substr(2, sl[1].length() - 2));
        tmpY = stoi(sl[2].substr(2, sl[2].length() - 2));
        text.setPos(tmpX, tmpY);
        this->fontSize = stoi ( sl[3].substr( 9, sl[3].length() - 9 ) );
        this->fontPath = sl[4].substr( 5, sl[4].length() - 5 );
        string tmpText = sl[7];
        text.setText(tmpText);
        this->fontColor = getColorFromString( sl[5].substr( 6, sl[5].length() - 6 ) );
        text.setCol(this->fontColor);
    }
    else if(sl[0] == "Image" || sl[0] == "Sound")
        cout << sl[0] << "is not a Text" << endl;
    else
        cout << "Unknown type: " << sl[0] << endl;
    
}

void MyText::init(SDL_Renderer *renderer) {
    text.setRenderer(renderer);
    text.setPath(this->fontPath);
    text.setFontSize(this->fontSize);
    text.init();
}

void MyText::checkAndMove() {
    text.checkAndMove();
}

void MyText::render() {
    text.render();
}

void MyText::destroy() {
    text.destroy();
}
