#pragma once
#include <string>
#include <vector>
#include "utilities.h"

class Slide{
private:
    std::vector<std::vector<std::string>> Images;
    std::vector<std::vector<std::string>> Texts;
    std::vector<std::vector<std::string>> Sounds;
    int id = -1;
public:
    void insertVector(std::vector<std::string> vec, Resource type);
    void splitAndInsert(std::string str, Resource type);
    std::vector<std::string> getVector(int index, Resource type);
    unsigned long getSize(Resource type);
    unsigned long getTotalSize();
    void setId(int id);
    int getId();
};

class AllSlides{
private:
    std::vector<Slide> slides;
    std::string fileName;
public:
    void addSlide(Slide s);
    void setFile(std::string fileName);
    void loadSlideShow();
    void displaySlides();
    void displaySlideWithId(int id);
    Slide getSlide(int index);
    
};

void write(std::string fileName, std::string text, bool app);
int getNumLines(std::string fileName);
std::string getLine(std::string fileName, int line);
void displayFileError(std::string fileName);
void displayLineNumberOverflow(int number);
void displayFileNotSlideShow(std::string fileName);
bool isLineNumberWithinRange(std::string fileName, int toCheck);
void insertToFile(std::string fileName, std::string text, int line, bool add);
bool ifFileContains(std::string fileName, std::string text);
bool ifFileContains(std::string fileName, std::string text, int line);
bool ifStringContains(std::string text, std::string subString);
void deleteLineInFile(std::string fileName, int line);
void takeAwayEmptyLines(std::string fileName);
bool find(std::string str, char ch);
void displayVector(std::vector<std::string> vec);
void splitString(std::string theString, std::vector<std::string> &vec, char ch);
std::vector<std::string> split(std::string str);
void displaySlideInfo(Slide s);
int getLineWhichContains(std::string fileName, std::string text);
void replaceLine(std::string  fileName, std::string text, int line);

/* ----------------- Needed Functions --------------------- */
bool isFileSlideShow(std::string fileName);
bool isSlideWithinRange(std::string fileName, int toCheck);
int getSlideLineNumber(std::string fileName, int slide, bool start);
int getIdFromSlide(std::string fileName , int slide);
void displaySlideNumOverflow(int number);
int getNumSlides(std::string fileName);
/* ----------------- Needed Functions --------------------- */

/* ----------------- With Id Functions -------------------- */
int getSlideLineNumberWithId(std::string fileName, int id, bool start);
void displaySlideIdError(int id);
int getNumTexturesWithId(std::string fileName, int id);
void putToSlideWithId(std::string fileName, int id, std::string text);
void deleteSlideWithId(std::string fileName, int id);
void loadSlideWithId(Slide &s, std::string fileName, int id);
int getSlideIdNumber(std::string fileName, int slide);
bool ifSlideIdExists(std::string fileName, int slideId);
bool isSlideWithIdEmpty(std::string fileName, int id);
/* ----------------- With Id Functions -------------------- */
