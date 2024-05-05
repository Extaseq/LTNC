#ifndef _PLAYFIELD_H
#define _PLAYFIELD_H

#include "AssetManager.h"
#include "AudioManager.h"
#include "Graphics.h"
#include "UserInterface.h"
#include "Beatmap/Beatmap.h"

struct ScrollingBackground
{
    SDL_Texture* texture;

    int scrollingOffset = 0;

    void scroll(int distance)
    {
        scrollingOffset -= distance;

        if (scrollingOffset < 0) scrollingOffset = 3840;
    }

};

class PlayField
{
private:

    const int FPS = 60;

    UI* scoreBar_bg;

    UI* scoreBar_color;

    UI* taiko_bar_left;

    UI* taiko_bar_right;

    UI* taikohitcircle;

    UI* taikohitcircleoverlay;

    AssetManager* mAssetMgr;

    Graphics* mGraphics;

    AudioManager* mAudioMgr;

    ScrollingBackground taikoslider;

public:

    PlayField(const Beatmap& beatmap, int diffIndex);

    void Open();

    void Update();

    void Render();
};

#endif // _PLAYFIELD_H
