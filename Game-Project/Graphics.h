#ifndef _GRAPHICS_H
#define _GRAPHICS_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include <stdio.h>
#include <string>

class Graphics {

public:

    static const int SCREEN_WIDTH = 1920;

    static const int SCREEN_HEIGHT = 1080;

private:

    static Graphics* sInstance;

    static bool sInitialized;

    SDL_Window* mWindow;

    TTF_Font* mFont;

public:

    static Graphics* Instance();

    static SDL_Renderer* mRenderer;

    static void Release();

    static bool Initialized();

    SDL_Texture* LoadTexture(const std::string& path);

    SDL_Texture* LoadText(const std::string& text, int size, bool dimmed = false);

    void LoadFont(int size);

    void ClearBackbuffer();

    void DrawTexture(SDL_Texture* tex, const SDL_FRect *dstRec, SDL_Rect *srcRect = NULL, double angle = 0);

    void DrawText(SDL_Texture* text, int x, int y);

    void Render();

private:

    Graphics();

    ~Graphics();

    bool Init();
};

#endif // _GRAPHICS_H

