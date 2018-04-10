#pragma once
#include "utilities.h"
#include "mySlide.h"

void initUI();
void processMainUI();
void renderMainUI();
void renderInputUI();
void processInputUI();
void destroyUI();
void setActionsForAll();
void processSaveButton(MySlide&);
void processNewImageButton(MySlide&);
void processNewTextButton(MySlide&);
void processNewSoundButton(MySlide&);
void processOpenButton();
void processCloseButton();
void processNewSlideButton();
void processNewFileButton();


