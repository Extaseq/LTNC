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

    PlayTime = "Played by Player in: " + Timer::Instance()->GetDate();
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

    Graphics::Instance()->DrawNumber(score, 500, 365, 2);

    Graphics::Instance()->DrawNumber(std::to_string(GreatCount), 400, 650, 1.5);

    Graphics::Instance()->DrawNumber(std::to_string(OkCount), 400, 900, 1.5);

    Graphics::Instance()->DrawNumber(std::to_string(MissCount), 1250, 1180, 1.5);

    Graphics::Instance()->DrawNumber(std::to_string(maxCombo), 100, 1480, 1.4);

    Graphics::Instance()->DrawNumber(_to_string(Accuracy), 980, 1480, 1.4);

    Cursor::Instance()->Render();

    Graphics::Instance()->DrawText(Graphics::Instance()->LoadText(Info, 80), 30, 30);
    Graphics::Instance()->DrawText(Graphics::Instance()->LoadText(PlayTime, 60), 30, 120);
}
