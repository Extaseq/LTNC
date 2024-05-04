#ifndef _SPRITE_H
#define _SPRITE_H

#include <SDL.h>
#include <SDL_image.h>

#include <vector>

#include "MyVector.h"
#include "Cursor.h"
#include "AssetManager.h"

class Sprite
{
private:

    MyVector pos;

    int frames;

    int index = 0;

    int scale = 1;

    std::string fileName;

public:

    SDL_FRect dstRect;

    SDL_Rect srcRect;

    Sprite(const std::string& spriteName, int frames_);

    void Update();

    void Draw();
};

#endif // _SPRITE_H
