#ifndef _CURSOR_H
#define _CURSOR_H

#include "AssetManager.h"

#define PI 3.14159265358979323846

class Cursor
{
private:

    static Cursor* sInstance;

    SDL_Texture* cursor;

    SDL_FRect RenderQuad;

    int x, y;

    double angle = 0;

public:

    static Cursor* Instance();

    void Release();

    void Update();

    void Render();

private:

    Cursor();

    ~Cursor();
};

#endif // _CURSOR_H
