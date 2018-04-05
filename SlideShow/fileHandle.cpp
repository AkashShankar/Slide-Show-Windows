#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "fileHandle.h"
using namespace std;

std::string theUniqueText = "***SlideShowApp***";

/* ----------- Slide Functions ------------- */
void Slide::insertVector(vector<string> vec, Resource type){
    if(type == TEXT)
        Texts.push_back(vec);
    else if(type == SOUND)
        Sounds.push_back(vec);
    else if(type == IMAGE)
        Images.push_back(vec);
}

void Slide::splitAndInsert(string str, Resource type){
    vector<string> newVector;
    newVector = split(str);
    displayVector(newVector);
    insertVector(newVector, type);
}

vector<string> Slide::getVector(int index, Resource type){
	if(type == IMAGE)
        return Images[index];
    else if(type == SOUND)
        return Sounds[index];
    else if(type == TEXT)
        return Texts[index];
    vector<string> empty;
	std::cout << "Returning empty string" << std::endl;
    return empty;
}

unsigned long Slide::getSize(Resource type){
    if(type == IMAGE)
        return Images.size();
    else if(type == SOUND)
        return Sounds.size();
    else if(type == TEXT)
        return Texts.size();
    return -1;
}

unsigned long Slide::getTotalSize(){
    return Images.size() + Texts.size() + Sounds.size();
}

void Slide::setId(int id){
    this->id = id;
}

int Slide::getId(){
    return this->id;
}
/* ----------- Slide Functions ------------- */


/* ----------- AllSlides Functions ------------- */
void AllSlides::addSlide(Slide s){
    this->slides.push_back(s);
}

void AllSlides::setFile(string fileName){
    this->fileName = fileName;
}

void AllSlides::loadSlideShow(){
    if(isFileSlideShow(this->fileName)){
        int numSlides = getNumSlides(this->fileName);
        for(int i=0;i<numSlides;i++){
            Slide tmp;
            int tmpId = getIdFromSlide(this->fileName, i+1);
            loadSlideWithId(tmp, fileName, tmpId);
            tmp.setId(tmpId);
            addSlide(tmp);
        }
    }
    else
        displayFileNotSlideShow(this->fileName);
}

void AllSlides::displaySlides(){
    unsigned long size = slides.size();
    for(unsigned long i=0;i<size; i++){
        cout << "SlideId : " << slides[i].getId() << endl;
        cout << "-------------------" << endl;
        displaySlideInfo(slides[i]);
        cout << "-------------------" << endl << endl;
    }
}

Slide AllSlides::getSlide(int index){
    return this->slides[index];
}

void AllSlides::displaySlideWithId(int id){
    if(ifSlideIdExists(this->fileName, id)){
        for(unsigned long i=0;i<slides.size();i++){
            if(id == slides[i].getId()){
                displaySlideInfo(slides[i]);
                break;
            }
        }
    }
    else
        displaySlideIdError(id);
}
/* ----------- AllSlides Functions ------------- */

void displayVector(vector<string> vec){
    for ( auto v: vec )
        cout << v << " ";
    cout << endl;
}

void displayFileError(string fileName){
    cout << "Cannot open " << fileName << endl;
}

void displayLineNumberOverflow(int number){
    cout << "Exceeding number of lines. Given : " << number << endl;
}

void displayFileNotSlideShow(string fileName){
    cout << "File not slideShow : " << fileName << endl;
}

void write(string fileName, string text, bool app){
    ofstream write;
    if(app)
        write.open(fileName.c_str(), ios::app);
    else
        write.open(fileName.c_str());
    if(!write){
        displayFileError(fileName);
        return;
    }
    write << text;
    write << "\n";
    write.close();
}

int getNumLines(string fileName){
    ifstream read(fileName.c_str());
    if(!read){
        displayFileError(fileName);
        return -1;
    }
    int numberOfLines = 0;
    while(!read.eof()){
        string line;
        getline(read, line);
        if(line != "")
            numberOfLines++;
    }
    read.close();
    return numberOfLines;
}

string getLine(string fileName, int line){
    ifstream read(fileName.c_str());
    if(!read){
        displayFileError(fileName);
        return "Error";
    }
    if(getNumLines(fileName) < line || line <= 0){
        displayLineNumberOverflow(line);
        read.close();
        return "Error";
    }
    int countLines = 0;
    while(!read.eof()){
        string text;
        getline(read, text);
        if(text != "")
            countLines++;
        if(line == countLines){
            read.close();
            return text;
        }
    }
    return "Error";
}

void insertToFile(string fileName, string text, int line, bool add){
    ifstream read(fileName);
    if(!read){
        displayFileError(fileName);
        return;
    }
    if(getNumLines(fileName) < line || line <= 0){
        displayLineNumberOverflow(line);
        return;
    }
    int countLines = 0;
    while(!read.eof()){
        string tmpText;
        getline(read, tmpText);
        if(tmpText != ""){
            countLines++;
            if(line == countLines){
                write("tmp.txt", text, true);
                if(add)
                    write("tmp.txt", tmpText, true);
            }
            else
                write("tmp.txt", tmpText, true);
        }
        
    }
    read.close();
    remove(fileName.c_str());
    rename("tmp.txt", fileName.c_str());
}

bool ifFileContains(string fileName, string text){
    ifstream read(fileName);
    if(!read){
        displayFileError(fileName);
        return false;
    }
    while(!read.eof()){
        string tmpText;
        getline(read, tmpText);
        if(ifStringContains(tmpText, text)){
            read.close();
            return true;
        }
    }
    return false;
}

bool ifFileContains(string fileName, string text, int line){
    string tmpText = getLine(fileName, line);
    return ifStringContains(tmpText, text);
}

bool ifStringContains(string text, string subString){
    if(text.find(subString) != string::npos)
        return true;
    return false;
}

bool isFileSlideShow(string fileName){
    return ifFileContains(fileName, theUniqueText, 1);
}

int getNumSlides(string fileName){
    if(isFileSlideShow(fileName)){
        string slideStartedText = "----------";
        int numLines = getNumLines(fileName);
        int numSlides = 0;
        int countLines = 0;
        bool slideStarted = true;
        while(countLines++ < numLines){
            string text = getLine(fileName, countLines);
            if(text == slideStartedText && slideStarted){
                numSlides++;
                slideStarted = false;
            }
            else if(text == slideStartedText && !slideStarted)
                slideStarted = true;
        }
        return numSlides;
    }
    else
        displayFileNotSlideShow(fileName);
    return -1;
}

int getSlideLineNumber(string fileName, int slide, bool start){
    if(isSlideWithinRange(fileName, slide)){
        int totalNumSlides = getNumSlides(fileName);
        if(slide > totalNumSlides){
            displaySlideNumOverflow(slide);
            return -1;
        }
        string slideStartedText = "----------";
        int numLines = getNumLines(fileName);
        int numSlides = 0;
        int countLines = 0;
        int var = 0;
        while(countLines++ < numLines){
            string text = getLine(fileName, countLines);
            if(text == slideStartedText)
                var++;
            if(var % 2 != 0 && text == slideStartedText)
                numSlides++;
            if(numSlides == slide){
                if(start)
                    return countLines+2;
                else{
                    while((text = getLine(fileName, ++countLines)) != slideStartedText)
                        text = getLine(fileName, countLines);
                    return countLines-2;
                }
            }
        }
    }
    return -1;
}

int getIdFromSlide(string fileName , int slide){
    if(isFileSlideShow(fileName)){
        if(isSlideWithinRange(fileName, slide)){
            int startLine = getSlideLineNumber(fileName, slide, true) - 1;
            string tmpText = getLine(fileName, startLine);
            return stoi(tmpText);
        }
        else
            displaySlideNumOverflow(slide);
    }
    else
        displayFileNotSlideShow(fileName);
    return -1;
}

void displaySlideNumOverflow(int number){
    cout << "Slide number overflow : " << number << endl;
}

bool isSlideWithIdEmpty(string fileName, int id){
    if(ifSlideIdExists(fileName, id)){
        int start = getSlideLineNumberWithId(fileName, id, true);
        int end = getSlideLineNumberWithId(fileName, id, false);
        if(start > end)
            return true;
        return false;
    }
    else
        displaySlideIdError(id);
    return false;
}

void splitString(string theString, vector<string> &vec, char ch)
{
    int j = 0, i=-1;
    bool hasStarted = false;
    while(theString[++i] == ' ');
    for(;i<theString.length();i++)
    {
        if(hasStarted)
        {
            hasStarted = false;
            j = i;
        }
        if(i == theString.length() - 1)
        {
            break;
        }
        if(theString[i] == ch)
        {
            string cutWord = theString.substr(j,i-j);
            vec.push_back(cutWord);
            hasStarted = true;
        }
    }
    if(theString[i] == '\"')
        vec.push_back(theString.substr(j,i-j));
    else
        vec.push_back(theString.substr(j,i-j+1));
    
}

void takeAwayEmptyLines(string fileName){
    ifstream read(fileName);
    if(!read){
        displayFileError(fileName);
        return;
    }
    while(!read.eof()){
        string tmpText;
        getline(read, tmpText);
        bool spacesOnly = tmpText.find_first_not_of(' ') == tmpText.npos;
        if(tmpText != "" && !spacesOnly)
            write("tmp.txt", tmpText, true);
    }
    read.close();
    remove(fileName.c_str());
    rename("tmp.txt", fileName.c_str());
}

bool find(string str, char ch) {
    for(int i = 0; str[i] != '\0'; i++)
        if(str[i] == ch)
            return true;
    return false;
}

vector<string> split(string str) {
    vector<string> tmp;
    splitString(str, tmp, '\"');
    vector<string> finalStr;
    splitString(tmp[0], finalStr, ' ');
    if(find(str, '\"'))
    {
        finalStr.push_back(tmp[1]);
    }
    return finalStr;
}

void loadSlideWithId(Slide &s, string fileName, int id){
    if(ifSlideIdExists(fileName, id)){
        int startLine = getSlideLineNumberWithId(fileName, id, true);
        int numTextures = getNumTexturesWithId(fileName, id);
        for(int i=0; i < numTextures; i++){
            string text = getLine(fileName, startLine + i);
            vector<string> tmpVec = split(text);
            if(tmpVec[0] == "Image")
                s.insertVector(tmpVec, IMAGE);
            else if(tmpVec[0] == "Sound")
                s.insertVector(tmpVec, SOUND);
            else if(tmpVec[0] == "Text")
                s.insertVector(tmpVec, TEXT);
        }
    }
    else
        displaySlideIdError(id);
}

int getNumTexturesWithId(string fileName, int id){
    if(ifSlideIdExists(fileName, id)){
        int start = getSlideLineNumberWithId(fileName, id, true);
        int end = getSlideLineNumberWithId(fileName, id, false);
        return end - start + 1;
    }
    else
        displaySlideIdError(id);
    return -1;
}

void displaySlideInfo(Slide s){
    for(unsigned long i=0;i<s.getSize(IMAGE);i++)
        displayVector(s.getVector(i, IMAGE));
    for(unsigned long i=0;i<s.getSize(SOUND);i++)
        displayVector(s.getVector(i, SOUND));
    for(unsigned long i=0;i<s.getSize(TEXT);i++)
        displayVector(s.getVector(i, TEXT));
}

int getLineWhichContains(std::string fileName, std::string text)
{
	int totalLines = getNumLines(fileName);
	int count = 0;
	for (int i = 1; i <= totalLines; i++) {
		count++;
		std::string _tmp = getLine(fileName, i);
		if (_tmp == text)
			return count;
	}
	return -1;
}

void replaceLine(std::string fileName, std::string text, int line)
{
	int totalLines = getNumLines(fileName);
	if (line > totalLines)
		return;
	insertToFile(fileName, text, line, false);
}

void putToSlideWithId(string fileName, int id, string text){
    if(ifSlideIdExists(fileName, id)){
        int startLine = getSlideLineNumberWithId(fileName, id, true);
        insertToFile(fileName, text, startLine, true);
    }
    else
        displaySlideIdError(id);
}

void deleteLineInFile(string fileName, int line){
    if(isLineNumberWithinRange(fileName, line)){
        int countLines = 0;
        int numLines = getNumLines(fileName);
        while(countLines++ < numLines){
            string current = getLine(fileName, countLines);
            if(countLines != line){
                write("tmp.txt", current, true);
            }
        }
        remove(fileName.c_str());
        rename("tmp.txt", fileName.c_str());
    }
}

void deleteSlideWithId(string fileName, int id){
    if(ifSlideIdExists(fileName, id)){
        int startLine = getSlideLineNumberWithId(fileName, id, true) - 2;
        int numTextures = getNumTexturesWithId(fileName, id) + 3;
        for(int i = 0; i<numTextures; i++)
            deleteLineInFile(fileName, startLine);
    }
    else
        displaySlideIdError(id);
}

int getSlideIdNumber(string fileName, int slide){
    if(isSlideWithinRange(fileName, slide)){
		int startLine = getSlideLineNumber(fileName, slide, true) - 1;
        string tmpText = getLine(fileName, startLine);
        return stoi(tmpText);
    }
    return -1;
}

bool ifSlideIdExists(string fileName, int slideId){
    if(isFileSlideShow(fileName)){
        int totalSlides = getNumSlides(fileName);
        for( int i = 0; i < totalSlides; i++){
            int currentId = getSlideIdNumber(fileName, i+1);
			if (currentId == slideId) {
				return true;
			}
        }
        return false;
    }
    else
        displayFileNotSlideShow(fileName);
    return false;
}


bool isSlideWithinRange(string fileName, int toCheck){
    if(isFileSlideShow(fileName)){
        if(toCheck <= getNumSlides(fileName) && toCheck > 0)
            return true;
        else{
            displaySlideNumOverflow(toCheck);
            return false;
        }
    }
    else
        displayFileNotSlideShow(fileName);
    return false;
}

bool isLineNumberWithinRange(string fileName, int toCheck){
    int numLines = getNumLines(fileName);
    if(numLines == -1){
        cout << "Unable to open file : " << fileName << endl;
        return false;
    }
    if(toCheck <= numLines && toCheck > 0)
        return true;
    else{
        displayLineNumberOverflow(toCheck);
        return false;
    }
    return false;
}

int getSlideLineNumberWithId(string fileName, int id, bool start){
    if(ifSlideIdExists(fileName, id))
    {
        int totalSlides = getNumSlides(fileName);
        for( int i=0; i < totalSlides; i++ ){
            int startLine = getSlideLineNumber(fileName, i+1, true) - 1;
            int endLine = getSlideLineNumber(fileName, i+1, false) + 1;
            string tmpText = getLine(fileName, startLine);
            int currentId = stoi(tmpText);
            if(currentId == id && start)
                return startLine+1;
            else if(currentId == id && !start)
                return endLine;
        }
    }
    else
        displaySlideIdError(id);
    return -1;
}

void displaySlideIdError(int id){
    cout << "Slide with id : " << id << " does not exist" << endl;
}
