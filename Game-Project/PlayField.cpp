#include "PlayField.h"

PlayField::PlayField(const Beatmap& beatmap, int diffIndex)
{
    mAssetMgr = AssetManager::Instance();
    mGraphics = Graphics::Instance();
    mAudioMgr = AudioManager::Instance();

    playSections.push_back(new Button("taiko-bar-left", 0, 610, 510, 492 + 50));

    playSections.push_back(new Button("taiko-bar-right", 510, 616, 3840 - 510, 476 + 50));

    playSections.push_back(new Button("taikohitcircle", 605, 768 - 30, 236, 236));

    playSections.push_back(new Button("taikohitcircleoverlay", 575, 739 - 30, 296, 296));

    playSections.push_back(new Button("scorebar-bg", 0, 0, 3840, 2160));

    playSections.push_back(new Button("scorebar-colour", 14, 44, 1363, 157));

    // Pause menu
    PauseMenu = new Menu("pause-overlay");

    PauseMenu->AddButton(new Button("pause-overlay", 0, 0, 3840, 2160));

    PauseMenu->AddButton(new Button("pause-continue", 360, 285, 3109, 686, true, 2));

    PauseMenu->AddButton(new Button("pause-retry", 1342, 968, 1145, 317, true, 2));

    PauseMenu->AddButton(new Button("pause-back", 390, 1343, 3052, 556, true, 2));

    // background = mAssetMgr->GetTexture(beatmap.beatmapMetadata.BackgroundFile);

    taikoslider.texture = mAssetMgr->GetTexture("Res\\taiko-Slider@2x.png");

    audioFile = beatmap.beatmapMetadata.AudioFileDir;

    while (Open() == true) {}
}

int GetButtonOpening(const std::string& button_name)
{
    if (button_name == "pause-continue") return CONTINUE;

    if (button_name == "pause-retry") return RETRY;

    if (button_name == "pause-back") return BACK;
}

void PlayField::Kats(bool left)
{
    SDL_FRect dstRect = {0, 608, 254, 546};
    std::string path = "Res\\taiko-drum-inner-right@2x.png";
    if (!left)
    {
        dstRect = {254, 608, 254, 546};
        path = "Res\\taiko-drum-inner-left@2x.png";
    }

    mGraphics->DrawTexture(mAssetMgr->GetTexture(path), &dstRect, NULL, 180);
}

void PlayField::Dons(bool right)
{
    SDL_FRect dstRect = {0, 608, 254, 546};
    std::string path = "Res\\taiko-drum-outer-right@2x.png";
    if (!right)
    {
        dstRect = {254, 608, 254, 546};
        path = "Res\\taiko-drum-outer-left@2x.png";
    }

    mGraphics->DrawTexture(mAssetMgr->GetTexture(path), &dstRect, NULL, 180);
}

void PlayField::Update()
{
    taikoslider.scroll(1);
}

void PlayField::Render()
{
    mGraphics->DrawText(taikoslider.texture, taikoslider.scrollingOffset, 0);

    mGraphics->DrawText(taikoslider.texture, taikoslider.scrollingOffset - 3840, 0);

    for (Button* section : playSections) section->Draw();
}

void PlayField::HandleKeyboard()
{

}

bool PlayField::Open()
{
    int HP = 100;

    mAudioMgr->PlayMusic(audioFile, 0);

    const int frameDelay = 1000 / FPS;

    Uint32 frameStart;
    int frameTime;

    while (Mix_PlayingMusic() == 1)
    {
        frameStart = SDL_GetTicks();

        /*- Update -*/
        Update();


        mGraphics->ClearBackbuffer();

        /*- Render -*/
        Render();

        /**/

        SDL_PumpEvents();

        while (SDL_PollEvent(&mEvent))
        {
            if (mEvent.type == SDL_KEYDOWN && mEvent.key.repeat == 0)
            {
                if (mEvent.key.keysym.sym == SDLK_d)
                {
                    Dons(true);
                }
                if (mEvent.key.keysym.sym == SDLK_f)
                {
                    Kats(true);
                }
                if (mEvent.key.keysym.sym == SDLK_j)
                {
                    Kats(false);
                }
                if (mEvent.key.keysym.sym == SDLK_k)
                {
                    Dons(false);
                }
                if (mEvent.key.keysym.sym == SDLK_ESCAPE)
                {
                    Mix_PauseMusic();
                    int CHOICE = OpenMenu(PauseMenu);
                    switch (CHOICE)
                    {
                    case CONTINUE:
                        break;

                    case RETRY:
                        return true;
                        break;

                    case BACK:
                        Mix_HaltMusic();
                        return false;

                    default:
                        break;
                    }
                    Mix_ResumeMusic();
                }
            }
        }

        /**/
        mGraphics->Render();

        frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime)
        {
            SDL_Delay(frameDelay - frameTime);
        }
    }

    Mix_HaltMusic();
    return false;
}

int PlayField::OpenMenu(Menu* menu)
{
    const int frameDelay = 1000 / FPS;

    Uint32 frameStart;
    int frameTime;

    while (true)
    {
        frameStart = SDL_GetTicks();

        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                std::string choice = menu->GetButtonClicked();

                if (choice != "NULL") return GetButtonOpening(choice);
            }
        }

        menu->Update();

        mGraphics->ClearBackbuffer();

        menu->Draw();

        Cursor::Instance()->Render();

        mGraphics->Render();

        frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime)
        {
            SDL_Delay(frameDelay - frameTime);
        }
    }
}
