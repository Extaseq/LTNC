#include "PlayField.h"

PlayField::PlayField(const Beatmap& beatmap, int diffIndex)
{
    mAssetMgr = AssetManager::Instance();

    mGraphics = Graphics::Instance();

    mAudioMgr = AudioManager::Instance();

    scoreBar_bg = new UI("scorebar-bg", 0, 0, 3840, 2160, false);

    scoreBar_color = new UI("scorebar-colour", 14, 44, 1363, 157, false);

    taiko_bar_left = new UI("taiko-bar-left", 0, 610, 510, 492, false);

    taiko_bar_right = new UI("taiko-bar-right", 510, 616, 3840 - 510, 476, false);

    taikohitcircle = new UI("taikohitcircle", 605, 768 - 30, 236, 236, false);

    taikohitcircleoverlay = new UI("taikohitcircleoverlay", 575, 739 - 30, 296, 296, false);

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

    taiko_bar_left->Render();

    taiko_bar_right->Render();

    taikohitcircle->Render();

    taikohitcircleoverlay->Render();

    scoreBar_bg->Render();

    scoreBar_color->Render();
}

void PlayField::Open()
{
    const int frameDelay = 1000 / FPS;

    Uint32 frameStart;
    int frameTime;

    while (Mix_PlayingMusic() == 1)
    {
        frameStart = SDL_GetTicks();

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
