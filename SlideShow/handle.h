#pragma once

void loop(void(*eventFunc)(void) , void(*mainScreenRender)(void), void(*inputScreenRender)(void),
          void(*quitFunc)(void), void(*updateFunc)(void));
