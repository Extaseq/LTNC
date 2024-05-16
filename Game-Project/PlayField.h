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
#include "Timer.h"

#include <deque>
#include <queue>
#include <vector>
#include <unordered_map>

using Int64 = int64_t;

#define CONTINUE 1
#define RETRY 2
#define BACK 3

#define MAX_HP 200.0

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

struct HPBar
{
    const std::string source = "Res/scorebar-colour@2x.png";

    SDL_FRect dstRect = {14, 44, 1363, 157};
    SDL_Rect srcRect = {0, 0, 968, 111};

    const float DefaultDstX = 1363.0f;
    const int DefaultSrcX = 968;

    double hp = 0;

    void Update(double NewHp)
    {
        hp = (NewHp > MAX_HP) ? MAX_HP : (NewHp < 0) ? 0 : NewHp;

        dstRect.w = (hp * DefaultDstX) / MAX_HP;
    }

    void Draw()
    {
        if (hp <= 0) return;

        srcRect.w = (hp * DefaultSrcX) / MAX_HP;

        Graphics::Instance()->DrawTexture(
            AssetManager::Instance()->GetTexture(source), &dstRect, &srcRect
        );
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
    Timer* mTimer;
    HPBar* mHPBar;

    Int64 RetryOffset = 0;

    double CurrentHP, DrainRate;

    bool Playing = false, failed = false;

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
