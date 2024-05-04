#include "Graphics.h"

Graphics* Graphics::sInstance = nullptr;

SDL_Renderer* Graphics::mRenderer = nullptr;

bool Graphics::sInitialized = false;

Graphics* Graphics::Instance()
{
    if (sInstance == nullptr)
    {
        sInstance = new Graphics();
    }
    return sInstance;
}

void Graphics::Release()
{
    delete sInstance;
    sInstance = nullptr;

    sInitialized = false;
}

bool Graphics::Initialized()
{
    return sInitialized;
}

Graphics::Graphics()
{
    sInitialized = Init();
}

Graphics::~Graphics()
{
    SDL_DestroyWindow(mWindow);
    mWindow = nullptr;

    SDL_DestroyRenderer(mRenderer);
    mRenderer = nullptr;

    IMG_Quit();
    SDL_Quit();
}

bool Graphics::Init()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        printf("SDL Initialization Error: %s\n", SDL_GetError());
        return false;
    }

    mWindow = SDL_CreateWindow("Hehe", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH * 2, SCREEN_HEIGHT * 2, SDL_WINDOW_FULLSCREEN);

    if (mWindow == nullptr)
    {
        printf("Window Creation Error: %s\n", SDL_GetError());
        return false;
    }

    mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED);

    if (mRenderer == nullptr)
    {
        printf("Renderer Creation Error: %s\n", SDL_GetError());
        return false;
    }

    SDL_SetRenderDrawColor(mRenderer, 0x00, 0x00, 0x00, 0x00);

    printf("SDL Initialize Successfully.\n");

    return true;
}

SDL_Texture* Graphics::LoadTexture(const std::string& path)
{
    SDL_Surface* surface = IMG_Load(path.c_str());

    if (surface == nullptr)
    {
        printf("Image Load Error: Path(%s) - Error(%s).\n", path.c_str(), IMG_GetError());

        return nullptr;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(mRenderer, surface);

    if (texture == nullptr)
    {
        printf("Create Texure Error: %s.\n", SDL_GetError());

        return nullptr;
    }

    SDL_FreeSurface(surface);

    return texture;
}

void Graphics::ClearBackbuffer()
{
    SDL_RenderClear(mRenderer);
}

void Graphics::DrawTexture(SDL_Texture* tex, SDL_FRect *dstRect, SDL_Rect *srcRect)
{
    SDL_RenderCopyExF(mRenderer, tex, srcRect, dstRect, 0, NULL, SDL_FLIP_NONE);
}

void Graphics::Render()
{
    SDL_RenderPresent(mRenderer);
}

