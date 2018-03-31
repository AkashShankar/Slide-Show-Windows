#include "stdafx.h"
#include "screen.h"
#include "handle.h"

/* external variables */
extern Screen mainScreen;
extern Screen inputScreen;
/* external variables */

/* global variables */
SDL_Event event;
bool isRunning = true;
const Uint8* keyState = nullptr;
void(*eventFunction)(void);
void(*mainRenderer)(void);
void(*inputRenderer)(void);
/* global variables */

void handleEvent(Screen &sc){
    switch(event.window.event)
    {
        case SDL_WINDOW_HIDDEN:
            sc.shown = false;
            sc.minimized = false;
            break;
        case SDL_WINDOWEVENT_SHOWN:
            sc.shown = true;
            break;
        case SDL_WINDOWEVENT_MINIMIZED:
            sc.minimized = true;
            break;
        case SDL_WINDOWEVENT_EXPOSED:
            SDL_RenderPresent(sc.getRenderer());
            break;
        case SDL_WINDOWEVENT_ENTER:
            sc.mouseFocus = true;
            break;
        case SDL_WINDOWEVENT_LEAVE:
            sc.mouseFocus = false;
            break;
        case SDL_WINDOWEVENT_FOCUS_GAINED:
            sc.keyboardFocus = true;
            break;
        case SDL_WINDOWEVENT_FOCUS_LOST:
            sc.keyboardFocus = false;
            break;
        case SDL_WINDOWEVENT_RESTORED:
            sc.minimized = false;
            break;
        case SDL_WINDOWEVENT_CLOSE:
            SDL_HideWindow(sc.getWindow());
            sc.shown = false;
            break;
    }
}

void loop(void(*eventFunc)(void) , void(*mainScreenRender)(void), void(*inputScreenRender)(void) ,
          void(*quitFunc)(void), void(updateFunc)(void)){
    eventFunction = eventFunc;
    mainRenderer = mainScreenRender;
    inputRenderer = inputScreenRender;
    while(isRunning) {
        bool allWindowsClosed = true;
        keyState = SDL_GetKeyboardState(NULL);
        while(SDL_PollEvent(&event)) {
            if(event.type == SDL_QUIT)
                isRunning = false;
            if(event.type == SDL_WINDOWEVENT && event.window.windowID == mainScreen.windowId)
                handleEvent(mainScreen);
            else if(event.type == SDL_WINDOWEVENT && event.window.windowID == inputScreen.windowId)
                handleEvent(inputScreen);
            if(mainScreen.shown)
                allWindowsClosed = false;
            if(allWindowsClosed)
                isRunning = false;
            eventFunction();
        }
        updateFunc();
        mainScreen.render(mainRenderer);
        inputScreen.render(inputRenderer);
    }
    quitFunc();
}
