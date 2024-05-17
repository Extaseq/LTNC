#ifndef RANKING_H
#define RANKING_H

#include "Button.h"
#include "ScoreSystem.h"
#include "Graphics.h"
#include "AssetManager.h"
#include "Cursor.h"

#define SS_GREAT_PERCENT


class RankingPanel
{
private:

    int GreatCount = 0;

    int OkCount = 0;

    int MissCount = 0;

    int TotalObject = 0;

    double Accuracy = 100.0;

    int maxCombo = 0;

    std::string score;

    std::string Rank = "Res/ranking-";

    Button* back_button = nullptr;

    const std::string bg_file = "Res/ranking-panel@2x.png";

    SDL_FRect bgRect = {0, 290, 3840, 3863};
    SDL_FRect rankRect = {71, -2400, 6468, 6566};

    std::string Info = "";

    std::vector<SDL_Texture*> BmInfo;

public:

    RankingPanel(ScoreSystem* mScore, int TotalObject);

    ~RankingPanel();

    void SetInfo(const std::string& Artist, const std::string& Title, const std::string& DiffName);

    std::string GetRank();

    std::string _to_string(int score);

    std::string _to_string(double acc);

    void DrawNumber(const std::string& num, int x, int y, double scale = 1.0);

    void Open();

    void Update();

    void Render();
};

#endif // RANKING_H
