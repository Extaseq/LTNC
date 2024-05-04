#include "GameManager.h"

GameManager* GameManager::sInstance = nullptr;

SDL_Event GameManager::mEvent;

std::vector<Beatmap> GameManager::BeatmapList;

int index = 0;

int diffIndex = 0;

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
    std::srand(std::time(nullptr));

    mQuit = false;

    mGraphics = Graphics::Instance();

    mAudioMgr = AudioManager::Instance();

    if (!Graphics::Initialized())
    {
        mQuit = true;
    }

    mainScreen = mGraphics->LoadTexture("Res\\menu-background.jpg");

    clickToPlay = mGraphics->LoadText("- PRESS ANY BUTTON -", 180);

    LoadBeatmap();

    BeatmapListSize = BeatmapList.size();
}

GameManager::~GameManager()
{
    AssetManager::Release();

    Graphics::Release();
    mGraphics = nullptr;

    SelectionMode::Release();
    mainMenu = nullptr;
}

void GameManager::LoadBeatmap()
{
    freopen("logError.txt", "w", stdout);

    printf("Start here.\n");

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

void GameManager::FadeIn()
{
    SDL_SetTextureBlendMode(mainScreen, SDL_BLENDMODE_BLEND);

    Uint32 elapsedTime = 0;

    Uint32 startTime = SDL_GetTicks();

    while (elapsedTime <= 500)
    {
        int alpha = 255 * elapsedTime / 500;

        SDL_SetTextureAlphaMod(mainScreen, alpha);

        mGraphics->ClearBackbuffer();

        mGraphics->DrawTexture(mainScreen, NULL, NULL);

        Cursor::Instance()->Render();

        mGraphics->Render();

        elapsedTime = SDL_GetTicks() - startTime;
    }
}

void GameManager::MainScreen()
{
    FadeIn();

    while (true)
    {
        while (SDL_PollEvent(&mEvent))
        {
            if (mEvent.type == SDL_QUIT)
            {
                return;
            }
            if (mEvent.type == SDL_KEYDOWN || mEvent.type == SDL_MOUSEBUTTONDOWN)
            {
                mQuit = false;
                SelectionMode();
                FadeIn();
            }
        }
        mGraphics->ClearBackbuffer();

        mGraphics->DrawTexture(mainScreen, NULL, NULL);

        mGraphics->DrawText(clickToPlay, 900, 1420);

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
                mAudioMgr->PlaySFX("Res\\menu-play-click.ogg", -1);
                --index;
                diffIndex = 0;
                aKeyDown = true;
                Mix_HaltMusic();
            }
            else if (mEvent.key.keysym.sym == SDLK_d && !dKeyDown)
            {
                mAudioMgr->PlaySFX("Res\\menu-play-click.ogg", -1);
                ++index;
                diffIndex = 0;
                dKeyDown = true;
                Mix_HaltMusic();
            }
            else if (mEvent.key.keysym.sym == SDLK_w && !wKeyDown)
            {
                mAudioMgr->PlaySFX("Res\\menu-play-click.ogg", -1);
                wKeyDown = true;

                if (diffIndex == 0) return;

                --diffIndex;
            }
            else if (mEvent.key.keysym.sym == SDLK_s && !sKeyDown)
            {
                mAudioMgr->PlaySFX("Res\\menu-play-click.ogg", -1);
                sKeyDown = true;

                if (diffIndex == BeatmapList[index].beatmapDifficulty.size() - 1) return;

                ++diffIndex;
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
            if (mEvent.key.keysym.sym == SDLK_w)
            {
                wKeyDown = false;
            }
            if (mEvent.key.keysym.sym == SDLK_s)
            {
                sKeyDown = false;
            }
        }
        else if (mEvent.type == SDL_MOUSEBUTTONDOWN)
        {
            if (mainMenu->getButtonClicked(mEvent.button.x, mEvent.button.y) == "menu-back")
            {
                mAudioMgr->PlaySFX("Res\\menu-back-click.ogg", -1);

                SDL_Delay(100);
                mQuit = true;
            }
            if (mainMenu->getButtonClicked(mEvent.button.x, mEvent.button.y) == "selection-random-over")
            {
                mAudioMgr->PlaySFX("Res\\menuHit.ogg", -1);
                index = std::rand() % BeatmapListSize;
                diffIndex = 0;
                Mix_HaltMusic();
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

        mainMenu->Update(index, diffIndex);

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
