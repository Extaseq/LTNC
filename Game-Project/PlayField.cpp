#include "PlayField.h"

PlayField::PlayField(const Beatmap& beatmap, int diffIndex)
{
    mAssetMgr = AssetManager::Instance();

    mGraphics = Graphics::Instance();

    mAudioMgr = AudioManager::Instance();

    playSections.push_back(new Button("taiko-bar-left", 0, 610, 510, 492));

    playSections.push_back(new Button("taiko-bar-right", 510, 616, 3840 - 510, 476));

    playSections.push_back(new Button("taikohitcircle", 605, 768 - 30, 236, 236));

    playSections.push_back(new Button("taikohitcircleoverlay", 575, 739 - 30, 296, 296));

    playSections.push_back(new Button("scorebar-bg", 0, 0, 3840, 2160));

    playSections.push_back(new Button("scorebar-colour", 14, 44, 1363, 157));

    // Pause menu

    pauseMenu.push_back(new Button("pause-overlay", 0, 0, 3840, 2160));

    pauseMenu.push_back(new Button("pause-continue", 360, 285, 3109, 686, true, 2));

    pauseMenu.push_back(new Button("pause-retry", 1342, 968, 1145, 317, true, 2));

    pauseMenu.push_back(new Button("pause-back", 390, 1343, 3052, 556, true, 2));

    // background = mAssetMgr->GetTexture(beatmap.beatmapMetadata.BackgroundFile);

    taikoslider.texture = mAssetMgr->GetTexture("Res\\taiko-Slider@2x.png");

    SDL_Delay(1000);

    mAudioMgr->PlayMusic(beatmap.beatmapMetadata.AudioFileDir, 0);

    Open();
}

void PlayField::Update()
{
    taikoslider.scroll(1);
}

void PlayField::Render()
{
    mGraphics->DrawText(taikoslider.texture, taikoslider.scrollingOffset, 0);

    mGraphics->DrawText(taikoslider.texture, taikoslider.scrollingOffset - 3840, 0);

    for (Button* section : playSections)
    {
        section->Render();
    }
}

void PlayField::Open()
{
    int HP = 100;

    const int frameDelay = 1000 / FPS;

    Uint32 frameStart;
    int frameTime;

    while (Mix_PlayingMusic() == 1)
    {
        frameStart = SDL_GetTicks();

        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.key.keysym.sym == SDLK_ESCAPE)
            {
                Mix_PauseMusic();
                OpenPauseMenu();
                Mix_ResumeMusic();
            }
        }

        Update();

        mGraphics->ClearBackbuffer();

        Render();

        mGraphics->Render();

        frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime)
        {
            SDL_Delay(frameDelay - frameTime);
        }
    }

    Mix_HaltMusic();
}

void PlayField::OpenPauseMenu()
{
    const int frameDelay = 1000 / FPS;

    Uint32 frameStart;
    int frameTime;

    bool open = true;

    while (open)
    {
        frameStart = SDL_GetTicks();

        for (Button* section : pauseMenu)
        {
            section->Update();
        }

        mGraphics->ClearBackbuffer();

        for (Button* section : pauseMenu)
        {
            section->Render();
        }

        Cursor::Instance()->Render();

        mGraphics->Render();

        frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime)
        {
            SDL_Delay(frameDelay - frameTime);
        }
    }
}
