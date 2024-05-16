#ifndef RANKING_H
#define RANKING_H

#include "Button.h"
#include "ScoreSystem.h"
#include "Graphics.h"
#include "AssetManager.h"

#define SS_GREAT_PERCENT


class RankingPanel
{
private:

    int GreatCount = 0;

    int OkCount = 0;

    int MissCount = 0;

    int TotalObject = 0;

    Button* back_button = nullptr;

    const std::string bg_file = "Res/ranking-panel@2x.png";

    SDL_FRect dstRect = {0, 291, 3840, 3863};

public:

    RankingPanel(ScoreSystem* mScore, int TotalObject);

    ~RankingPanel();

    int GetRank()
    {

    }

    void Update();

    void Render();
};

#endif // RANKING_H
