#include "GameManager.h"

GameManager* GameManager::sInstance = nullptr;

SDL_Event GameManager::mEvent;

std::vector<Beatmap> GameManager::BeatmapList;

int index = 0;

GameManager* GameManager::Instance()
{
    if (sInstance == nullptr)
    {
        sInstance = new GameManager();
    }
    return sInstance;
}

void GameManager::Release()
{
    delete sInstance;

    sInstance = nullptr;
}

GameManager::GameManager()
{
    mQuit = false;

    mGraphics = Graphics::Instance();

    if (!Graphics::Initialized())
    {
        mQuit = true;
    }

    mainScreen = mGraphics->LoadTexture("Res\\menu-background.jpg");

    LoadBeatmap();

    BeatmapListSize = BeatmapList.size();
}

GameManager::~GameManager()
{
    Graphics::Release();
    mGraphics = nullptr;

    SelectionMode::Release();
    mainMenu = nullptr;
}

void GameManager::LoadBeatmap()
{
    freopen("logError.txt", "w", stdout);

    DIR* dir;

    struct dirent *entry;

    if ((dir = opendir(BEATMAP_FOLDER.c_str())) != NULL)
    {
        while ((entry = readdir(dir)) != NULL)
        {
            std::string beatmapName = entry->d_name;

            if (beatmapName.size() > 2)
            {
                BeatmapList.push_back(Beatmap());

                Decoder::getDecoder(beatmapName, BeatmapList.back());
            }
        }
    }

    freopen("CON", "w", stdout);

    printf("Beatmap Loaded Successfully.\n");
}

void GameManager::MainScreen()
{
    while (true)
    {
        while (SDL_PollEvent(&mEvent))
        {
            if (mEvent.type == SDL_QUIT)
            {
                mQuit = true;
            }
            if (mEvent.type == SDL_KEYDOWN)
            {
                mQuit = false;
                SelectionMode();
            }
        }
        mGraphics->ClearBackbuffer();

        mGraphics->DrawTexture(mainScreen, NULL, NULL);

        Cursor::Instance()->Render();

        mGraphics->Render();
    }
}

void GameManager::handleKeyboard()
{
    while (SDL_PollEvent(&mEvent))
    {
        if (mEvent.type == SDL_QUIT)
        {
            mQuit = true;
        }
        else if (mEvent.type == SDL_KEYDOWN)
        {
            if (mEvent.key.keysym.sym == SDLK_ESCAPE)
            {
                mQuit = true;
            }
            else if (mEvent.key.keysym.sym == SDLK_a && !aKeyDown)
            {
                --index;
                aKeyDown = true;
            }
            else if (mEvent.key.keysym.sym == SDLK_d && !dKeyDown)
            {
                ++index;
                dKeyDown = true;
            }
        }
        else if (mEvent.type == SDL_KEYUP)
        {
            if (mEvent.key.keysym.sym == SDLK_a)
            {
                aKeyDown = false;
            }
            if (mEvent.key.keysym.sym == SDLK_d)
            {
                dKeyDown = false;
            }
        }
    }
}

void GameManager::SelectionMode()
{
    const int frameDelay = 1000 / FPS;

    Uint32 frameStart;
    int frameTime;

    mainMenu = SelectionMode::Instance();

    while (!mQuit)
    {
        frameStart = SDL_GetTicks();

        handleKeyboard();

        if (index < 0) index += BeatmapListSize;
        if (index >= BeatmapListSize) index %= BeatmapListSize;

        mGraphics->ClearBackbuffer();

        mainMenu->Update(index);

        mainMenu->Render();

        Cursor::Instance()->Render();

        mGraphics->Render();

        frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime)
        {
            SDL_Delay(frameDelay - frameTime);
        }
    }
}
