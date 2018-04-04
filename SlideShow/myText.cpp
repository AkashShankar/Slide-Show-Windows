#include "stdafx.h"
#include <iostream>
#include "myText.h"
#include "fileHandle.h"
#include "utilities.h"
using namespace std;

void MyText::setInfo(vector<string> sl) {
    
    if(sl[0] == "Text") {
		_vec = sl;
		current = getStringFromVector(_vec);
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

std::string MyText::customGetStringFromVector(std::vector<std::string> &t) {
	std::string tmp;
	for (int i = 0; i <= 5; i++) {
		tmp += t[i];
		if (i != 5)
			tmp += " ";
	}
	tmp += " ";
	tmp += t[6];
	tmp += t[7];
	return tmp;
}

void MyText::save(std::string fileName) {
	std::vector < std::string> _tmpVec2 = _vec;
	std::vector<std::string> _tmpVec = getUpdatedVector();
	

	std::string lastString = _tmpVec[7];
	std::string finalString = "\"";
	finalString += lastString;
	finalString += "\"";
	_tmpVec.erase(_tmpVec.begin() + 7);
	_tmpVec.push_back(finalString);

	lastString = _tmpVec2[7];
	finalString = "\"";
	finalString += lastString;
	finalString += "\"";
	_tmpVec2.erase(_tmpVec2.begin() + 7);
	_tmpVec2.push_back(finalString);

	current = customGetStringFromVector(_tmpVec2);

	std::string _tmpStr = customGetStringFromVector(_tmpVec);
	int line = getLineWhichContains(fileName, current);
	replaceLine(fileName, _tmpStr, line);
	current = _tmpStr;
}

std::vector<std::string> MyText::getUpdatedVector() {
	std::string tmp;
	tmp = "x:";
	tmp += std::to_string(text.rect.x);
	_vec.erase(_vec.begin() + 1);
	_vec.insert(_vec.begin() + 1, tmp);

	tmp = "y:";
	tmp += std::to_string(text.rect.y);
	_vec.erase(_vec.begin() + 2);
	_vec.insert(_vec.begin() + 2, tmp);
	
	return _vec;
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
