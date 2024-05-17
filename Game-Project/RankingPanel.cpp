#include "RankingPanel.h"

RankingPanel::RankingPanel(ScoreSystem* mScore, int TotalObject)
{
    this->GreatCount = mScore->GetGreat();
    this->OkCount = mScore->GetOk();
    this->MissCount = mScore->GetMiss();
    this->Accuracy = mScore->GetAccuracy();
    this->TotalObject = TotalObject;
    this->score = _to_string(mScore->GetScore());
    this->maxCombo = mScore->GetMaxCombo();

    back_button = new Button("menu-back", 0, 1896, 596, 264, true, HOVER_TYPE_GLOW);

    Rank += GetRank() + "@2x.png";
}

RankingPanel::~RankingPanel() {}

void RankingPanel::SetInfo(const std::string& Artist, const std::string& Title, const std::string& DiffName)
{
    Info = Artist + " - " + Title + " [" + DiffName + "]";
}

std::string RankingPanel::GetRank()
{
    if (Accuracy == 100.0) return "X";

    if ((static_cast<double>(GreatCount) / TotalObject) >= 0.9)
    {
        return "S";
    }
    if ((static_cast<double>(GreatCount) / TotalObject) >= 0.8)
    {
        return "A";
    }
    if ((static_cast<double>(GreatCount) / TotalObject) >= 0.7)
    {
        return "B";
    }
    if ((static_cast<double>(GreatCount) / TotalObject) >= 0.6)
    {
        return "C";
    }
    return "D";
}

std::string RankingPanel::_to_string(int score)
{
    std::ostringstream oss;
    oss << std::setw(8) << std::setfill('0') << score;
    return oss.str();
}

std::string RankingPanel::_to_string(double acc)
{
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(2) << acc;
    return oss.str();
}

void RankingPanel::DrawNumber(const std::string& num, int x, int y, double scale)
{
    SDL_FRect dst = {x, y, 74.7 * scale, 90 * scale};

    for (size_t i = 0; i < num.size(); ++i)
    {
        if (num[i] == '.')
        {
            dst.x -= (10 * scale);
            Graphics::Instance()->DrawTexture(
                AssetManager::Instance()->GetTexture(
                    "Res/Assets/score/score-dot@2x.png"
                ), &dst, NULL
            );
            dst.x += (20 * scale);
        }
        else
        {
            Graphics::Instance()->DrawTexture(
                AssetManager::Instance()->GetTexture(
                    "Res/Assets/score/score-" + std::to_string(num[i] - '0') + "@2x.png"
                ), &dst, NULL
            );
            dst.x += (55 * scale);
        }
    }
}

void RankingPanel::Open()
{
    SDL_Event mEvent;
    while (true)
    {
        while (SDL_PollEvent(&mEvent))
        {
            if (mEvent.type == SDL_MOUSEBUTTONDOWN)
            {
                if (back_button->OnMouseHover())
                {
                    return;
                }
            }
        }
        Update();

        Graphics::Instance()->ClearBackbuffer();
        Render();
        Graphics::Instance()->Render();
    }
}

void RankingPanel::Update()
{
    back_button->Update();
}

void RankingPanel::Render()
{
    Graphics::Instance()->ClearBackbuffer();

    Graphics::Instance()->DrawTexture(
        AssetManager::Instance()->GetTexture(bg_file), &bgRect, NULL
    );

    back_button->Draw();

    Graphics::Instance()->DrawTexture(
        AssetManager::Instance()->GetTexture(Rank), &rankRect, NULL
    );

    DrawNumber(score, 500, 365, 2);

    DrawNumber(std::to_string(GreatCount), 400, 650, 1.5);

    DrawNumber(std::to_string(OkCount), 400, 900, 1.5);

    DrawNumber(std::to_string(MissCount), 1250, 1180, 1.5);

    DrawNumber(std::to_string(maxCombo), 100, 1480, 1.4);

    DrawNumber(_to_string(Accuracy), 980, 1480, 1.4);

    Cursor::Instance()->Render();

    Graphics::Instance()->DrawText(Graphics::Instance()->LoadText(Info, 80), 30, 30);
}
