#ifndef _PLAYFIELD_H
#define _PLAYFIELD_H

#include "AudioManager.h"
#include "Graphics.h"
#include "Beatmap/Beatmap.h"
#include "Cursor.h"
#include "Menu.h"

#include <deque>
#include <vector>

#define CONTINUE 1
#define RETRY 2
#define BACK 3

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

    Menu* PauseMenu, * FailMenu;

    SDL_Event mEvent;

    std::string audioFile;

    AssetManager* mAssetMgr;
    Graphics* mGraphics;
    AudioManager* mAudioMgr;

    ScrollingBackground taikoslider;

public:

    PlayField(const Beatmap& beatmap, int diffIndex);

    bool Open();

    void Kats(bool left);

    void Dons(bool right);

    int OpenMenu(Menu* menu);

    void Update();

    void HandleKeyboard();

    void Render();
};

#endif // _PLAYFIELD_H
