#ifndef _PLAYFIELD_H
#define _PLAYFIELD_H

#include "AudioManager.h"
#include "Graphics.h"
#include "Beatmap/Beatmap.h"
#include "Cursor.h"
#include "Menu.h"
#include "HitCircle.h"
#include "InputManager.h"
#include "ScoreSystem.h"

#include <deque>
#include <queue>
#include <vector>
#include <unordered_map>

using Int64 = int64_t;

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

    std::vector<Button*> playSections;

    std::priority_queue<HitCircle, std::vector<HitCircle>, HitCircleComparator> Waiting;

    std::deque<HitCircle> OnScreen;

    Menu* PauseMenu,* FailMenu,* ScorePanel;

    SDL_Event mEvent;

    bool LastMenuOpened = false;

    std::string audioFile;

    std::vector<HitObject> mHitObjects;

    AssetManager* mAssetMgr;
    Graphics* mGraphics;
    AudioManager* mAudioMgr;
    InputManager* mInputMgr;
    ScoreSystem* mScore;

    Int64 RetryOffset = 0;

    double TotalHP, HP;

    bool Playing = false;

    ScrollingBackground taikoslider;

public:

    PlayField(const Beatmap& beatmap, int DiffIndex);

    bool Open();

    void LoadBeatmap(const Beatmap& beatmap, int DiffIndex);

    void Kats(bool left, Int64 Time);
    void Dons(bool right, Int64 Time);

    void PlayButton(Int64 Time, int Type);

    int OpenMenu(Menu* menu);

    void Update(int deltaTime);

    void Render();
};

#endif // _PLAYFIELD_H
