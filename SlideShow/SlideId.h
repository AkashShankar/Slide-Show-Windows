#pragma once
#include "fileHandle.h"

class SlideId {
private:
	std::string fileName;
public:
	int currentIndex{ -1 };
	int currentId{ -1 };
	std::vector<int> _ids;
public:
	inline void setFile(std::string fileName) { this->fileName = fileName; }
	inline int getNumIds() { return _ids.size(); }
	void loadAllIds();
	void updateId();
	void incrementIndex();
	void decrementIndex();
	void displayCurrent();
	void displayAllIds();
};