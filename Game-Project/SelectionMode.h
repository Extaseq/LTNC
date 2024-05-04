#ifndef _MENU_H
#define _MENU_H

#include <SDL.h>
#include <SDL_image.h>

#include <stdio.h>
#include <vector>

#include "Graphics.h"
#include "Sprite.h"

class SelectionMode
{
private:

    static SelectionMode* sInstance;

    std::vector<Sprite*> UI;

    Graphics* mGraphics;

    SDL_Texture* background;

    int prevIndex = -1;

public:

    static SelectionMode* Instance();

    static void Release();

    void Update(int index);

    void Render();

private:

    SelectionMode();

    ~SelectionMode();
};

#endif // _MENU_H
