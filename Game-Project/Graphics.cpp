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

    TTF_Quit();
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

    mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (mRenderer == nullptr)
    {
        printf("Renderer Creation Error: %s\n", SDL_GetError());
        return false;
    }

    if (TTF_Init() == -1)
    {
        printf("TTF Initialization Error: %s\n", TTF_GetError());
        return false;
    }

    SDL_SetRenderDrawColor(mRenderer, 0x00, 0x00, 0x00, 0x00);

    SDL_ShowCursor(SDL_DISABLE);

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

void Graphics::LoadFont(int size)
{
    mFont = TTF_OpenFont("Res\\Dosis-Variable.ttf", size);
    if (mFont == nullptr)
    {
        printf("Unable to Load Font: %s\n", TTF_GetError());
    }
}

SDL_Texture* Graphics::LoadText(const std::string& text, int size, bool dimmed)
{
    SDL_Color textColor;
    if (dimmed == true) textColor = {232, 133, 239, 0};
    else textColor = {255, 255, 255, 0};

    LoadFont(size);

    SDL_Surface* surface = TTF_RenderText_Solid(mFont, text.c_str(), textColor);
    if(surface == nullptr)
    {
        printf("Load text error: %s\n", TTF_GetError());
        return nullptr;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(mRenderer, surface);
    if(texture == nullptr)
    {
        printf("Create text error: %s\n", SDL_GetError());
    }
    SDL_FreeSurface(surface);
    return texture;
}

void Graphics::ClearBackbuffer()
{
    SDL_RenderClear(mRenderer);
}

void Graphics::DrawTexture(SDL_Texture* tex, const SDL_FRect *dstRect, SDL_Rect *srcRect, double angle)
{
    SDL_RenderCopyExF(mRenderer, tex, srcRect, dstRect, angle, NULL, SDL_FLIP_NONE);
}

void Graphics::DrawText(SDL_Texture* text, int x, int y)
{
    SDL_Rect dest;

    dest.x = x;
    dest.y = y;

    SDL_QueryTexture(text, NULL, NULL, &dest.w, &dest.h);

    SDL_RenderCopy(mRenderer, text, NULL, &dest);
}

void Graphics::DrawNumber(const std::string& num, int x, int y, double scale)
{
    SDL_FRect dst = {x, y, 74.7 * scale, 90 * scale};

    for (size_t i = 0; i < num.size(); ++i)
    {
        if (num[i] == '.')
        {
            dst.x -= (10 * scale);
            Graphics::Instance()->DrawTexture(
                AssetManager::Instance()->GetTexture(
                    "Res/Assets/score/score-dot@2x.png"
                ), &dst, NULL
            );
            dst.x += (20 * scale);
        }
        else
        {
            Graphics::Instance()->DrawTexture(
                AssetManager::Instance()->GetTexture(
                    "Res/Assets/score/score-" + std::to_string(num[i] - '0') + "@2x.png"
                ), &dst, NULL
            );
            dst.x += (55 * scale);
        }
    }
}

void Graphics::Render()
{
    SDL_RenderPresent(mRenderer);
}

