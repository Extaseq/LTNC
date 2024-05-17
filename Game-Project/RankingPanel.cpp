#include "RankingPanel.h"

RankingPanel::RankingPanel(ScoreSystem* mScore, int TotalObject)
{
    this->GreatCount = mScore->GetGreat();
    this->OkCount = mScore->GetOk();
    this->MissCount = mScore->GetMiss();
    this->Accuracy = mScore->GetAccuracy();
    this->TotalObject = TotalObject;

    back_button = new Button("menu-back", 0, 1896, 596, 264, true, HOVER_TYPE_GLOW);

    Rank += GetRank() + "@2x.png";
}

RankingPanel::~RankingPanel() {}

void RankingPanel::SetInfo(const std::string& Artist, const std::string& Title, const std::string& DiffName)
{
    Info = Artist + " - " + Title + "[" + DiffName + "]";
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
    Graphics::Instance()->DrawTexture(
        AssetManager::Instance()->GetTexture(bg_file), &bgRect, NULL
    );

    back_button->Draw();

    Graphics::Instance()->DrawTexture(
        AssetManager::Instance()->GetTexture(Rank), &rankRect, NULL
    );

    Cursor::Instance()->Render();

    Graphics::Instance()->DrawText(Graphics::Instance()->LoadText(Info, 80), 30, 30);
}
