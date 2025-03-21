#include "GameManager.h"

GameManager* GameManager::sInstance = nullptr;

SDL_Event GameManager::mEvent;

std::vector<Beatmap> GameManager::BeatmapList;

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

    mGraphics = Graphics::Instance();
    mAssetMgr = AssetManager::Instance();
    mAudioMgr = AudioManager::Instance();

    if (!Graphics::Initialized()) mQuit = true;

    mainScreen = mAssetMgr->GetTexture("Res\\menu-background.jpg");

    clickToPlay = mGraphics->LoadText("- PRESS ANY BUTTON -", 180);

    LoadBeatmap();

    BeatmapListSize = BeatmapList.size();

    mQuit = false;
}

GameManager::~GameManager()
{
    AssetManager::Release();
    mAssetMgr = nullptr;

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

    bool screen = true;

    while (screen)
    {
        while (SDL_PollEvent(&mEvent))
        {
            if (mEvent.key.keysym.sym == SDLK_ESCAPE)
            {
                screen = false;
                break;
            }
            else if (mEvent.type == SDL_KEYDOWN || mEvent.type == SDL_MOUSEBUTTONDOWN)
            {
                mQuit = false;
                mAudioMgr->PlaySFX("Res/menu-freeplay-click.ogg");
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

    SelectionMode::Release();
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
            else if (mEvent.key.keysym.sym == SDLK_RETURN)
            {
                mAudioMgr->PlaySFX("Res/menu-freeplay-click.ogg");
                Mix_HaltMusic();
                newGame = new PlayField(BeatmapList[bmIndex], diffIndex, Auto);
                delete newGame;
                newGame = nullptr;
                mQuit = false;
            }
            else if (mEvent.key.keysym.sym == SDLK_LEFT && !aKeyDown)
            {
                mAudioMgr->PlaySFX("Res/select-expand.ogg");
                --bmIndex;
                diffIndex = 0;
                aKeyDown = true;
                Mix_HaltMusic();
            }
            else if (mEvent.key.keysym.sym == SDLK_RIGHT && !dKeyDown)
            {
                mAudioMgr->PlaySFX("Res/select-expand.ogg");
                ++bmIndex;
                diffIndex = 0;
                dKeyDown = true;
                Mix_HaltMusic();
            }
            else if (mEvent.key.keysym.sym == SDLK_UP && !wKeyDown)
            {
                mAudioMgr->PlaySFX("Res/select-difficulty.ogg");
                wKeyDown = true;

                if (diffIndex == 0) return;

                --diffIndex;
            }
            else if (mEvent.key.keysym.sym == SDLK_DOWN && !sKeyDown)
            {
                mAudioMgr->PlaySFX("Res/select-difficulty.ogg");
                sKeyDown = true;

                if (diffIndex == (int)BeatmapList[bmIndex].beatmapDifficulty.size() - 1) return;

                ++diffIndex;
            }
        }
        else if (mEvent.type == SDL_KEYUP)
        {
            if (mEvent.key.keysym.sym == SDLK_LEFT)
            {
                aKeyDown = false;
            }
            if (mEvent.key.keysym.sym == SDLK_RIGHT)
            {
                dKeyDown = false;
            }
            if (mEvent.key.keysym.sym == SDLK_UP)
            {
                wKeyDown = false;
            }
            if (mEvent.key.keysym.sym == SDLK_DOWN)
            {
                sKeyDown = false;
            }
        }
        else if (mEvent.type == SDL_MOUSEBUTTONDOWN)
        {
            std::string TYPE = mainMenu->getButtonClicked();

            if (TYPE == "NULL") return;

            if (TYPE == "menu-back")
            {
                mAudioMgr->PlaySFX("Res\\back-button-click.ogg");

                SDL_Delay(100);
                mQuit = true;
            }
            if (TYPE == "selection-random-over")
            {
                mAudioMgr->PlaySFX("Res\\menuHit.ogg");
                bmIndex = std::rand() % BeatmapListSize;
                diffIndex = 0;
                Mix_HaltMusic();
            }

            if (TYPE == "selection-mods-over")
            {
                mAudioMgr->PlaySFX("Res\\menuHit.ogg", -1);
                Auto = (Auto + 1) % 2;
            }

            char num = TYPE.back();
            TYPE.pop_back();

            if (TYPE == "menu_button_")
            {
                if (diffIndex != (num - '0'))
                {
                    diffIndex = num - '0';
                }
                else
                {
                    mAudioMgr->PlaySFX("Res/menu-freeplay-click.ogg");
                    Mix_HaltMusic();
                    newGame = new PlayField(BeatmapList[bmIndex], diffIndex, Auto);
                    delete newGame;
                    newGame = nullptr;
                    mQuit = false;
                }
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

        if (bmIndex < 0) bmIndex += BeatmapListSize;
        if (bmIndex >= BeatmapListSize) bmIndex %= BeatmapListSize;

        mGraphics->ClearBackbuffer();

        mainMenu->Update(bmIndex, diffIndex);

        mainMenu->Render();

        if (Auto) mGraphics->DrawText(mGraphics->LoadText("Auto Enabled", 100), 400, 1800);

        Cursor::Instance()->Render();

        mGraphics->Render();

        frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime) SDL_Delay(frameDelay - frameTime);
    }
}
