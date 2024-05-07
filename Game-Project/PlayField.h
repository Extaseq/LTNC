#ifndef _PLAYFIELD_H
#define _PLAYFIELD_H

#include "AssetManager.h"
#include "AudioManager.h"
#include "Graphics.h"
#include "Button.h"
#include "Beatmap/Beatmap.h"
#include "Cursor.h"

#include <deque>
#include <vector>

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

    std::vector<Button*> playSections;

    std::vector<Button*> pauseMenu;

    AssetManager* mAssetMgr;

    Graphics* mGraphics;

    AudioManager* mAudioMgr;

    ScrollingBackground taikoslider;

public:

    PlayField(const Beatmap& beatmap, int diffIndex);

    void Open();

    void OpenPauseMenu();

    void Update();

    void Render();
};

#endif // _PLAYFIELD_H
