#include "RankingPanel.h"

RankingPanel::RankingPanel(ScoreSystem* mScore, int TotalObject)
{
    this->GreatCount = mScore->GetGreat();
    this->OkCount = mScore->GetOk();
    this->MissCount = mScore->GetMiss();
    this->TotalObject = TotalObject;

    back_button = new Button("menu-back", 0, 1896, 596, 264, true, HOVER_TYPE_GLOW);
}

RankingPanel::~RankingPanel() {}

void RankingPanel::Update()
{
    back_button->Update();
}

void RankingPanel::Render()
{
    Graphics::Instance()->DrawTexture(
        AssetManager::Instance()->GetTexture(bg_file), &dstRect, NULL
    );
}
