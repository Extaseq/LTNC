#include "ScoreSystem.h"

ScoreSystem* ScoreSystem::sInstance = nullptr;

ScoreSystem* ScoreSystem::Instance()
{
    if (sInstance == nullptr)
    {
        sInstance = new ScoreSystem();
    }
    return sInstance;
}

void ScoreSystem::Release()
{
    delete sInstance;
    sInstance = nullptr;
}

ScoreSystem::ScoreSystem() {}

ScoreSystem::~ScoreSystem() {}

int ScoreSystem::GetScore(double Time)
{
    if (Time <= GreatTime) {
        Great++;
        return GREAT;
    }

    if (Time <= OkTime) {
        Ok++;
        return OK;
    }
    Miss++;
    return MISS;
}

void ScoreSystem::SetOD(double OD)
{
    GreatTime = 50 - 3 * OD;

    if (OD < 5)
    {
        OkTime = 120 - 8 * OD;
        MissTime = 135 - 8 * OD;
    }
    else
    {
        OkTime = 110 - 6 * OD;
        MissTime = 120 - 5 * OD;
    }

    currentCombo = currentScore = 0;
    Great = Ok = Miss = 0;
}

void ScoreSystem::UpdateAccuracy()
{
    if (Great == 0 && Ok == 0 && Miss == 0) return;

    Accuracy = ((Great + 0.5 * Ok) / (Great + Ok + Miss)) * 100;
}

void ScoreSystem::SetMiss()
{
    currentCombo = 0;
    Miss++;
}

int ScoreSystem::AddScore(double Time, int ClickType, HitCircle &hitCircle, bool KiaiTime)
{
    Time = std::abs(Time);

    if (Time > MissTime) return NONE;

    if (ClickType != hitCircle.GetType())
    {
        currentCombo = 0;
        hitCircle.SetClicked();
        Miss++;
        return MISS;
    }

    int Score = GetScore(Time);

    if (Score == MISS)
    {
        currentCombo = 0;
        hitCircle.SetClicked();
        return MISS;
    }

    currentCombo++;

    currentScore += (
        (Score + std::min(currentCombo / 10, 10) * SCORE_MULTIPLIER) * (KiaiTime ? 1.2 : 1.0)
    );

    hitCircle.SetClicked();

    return Score;
}

std::string ScoreSystem::_to_string(double acc)
{
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(2) << acc;
    return oss.str();
}

void ScoreSystem::Render()
{
    UpdateAccuracy();
    long int tempScore = currentScore;
    std::string path = "Res/Assets/score/score-";
    SDL_FRect pos = {3757, 0, 83 * 0.9, 100 * 0.9};

    for (int i = 7; i >= 0; --i)
    {
        if (tempScore == 0)
        {
            Graphics::Instance()->DrawTexture(
                AssetManager::Instance()->GetTexture("Res/Assets/score/score-0@2x.png"), &pos, NULL
            );
            pos.x -= 63;
            continue;
        }

        Graphics::Instance()->DrawTexture(
            AssetManager::Instance()->GetTexture(path + char(tempScore % 10 + '0') + "@2x.png"), &pos, NULL
        );
        pos.x -= 63;
        tempScore /= 10;
    }


    pos = {0, 2000, 112, 134};
    std::string combo = std::to_string(currentCombo);
    for (size_t i = 0; i < combo.size(); ++i, pos.x += 100)
    {
        Graphics::Instance()->DrawTexture(
            AssetManager::Instance()->GetTexture(path + combo[i] + "@2x.png"), &pos, NULL
        );
    }
    Graphics::Instance()->DrawTexture(
        AssetManager::Instance()->GetTexture("Res/Assets/score/score-x@2x.png"), &pos, NULL
    );

    pos = {3825, 110, 40, 60};
    Graphics::Instance()->DrawTexture(
        AssetManager::Instance()->GetTexture("Res/Assets/score/score-percent@2x.png"), &pos, NULL
    );

    std::string acc = _to_string(Accuracy);
    std::reverse(acc.begin(), acc.end());

    pos.x -= 30;
    for (int i = 0; i < acc.size(); i++)
    {
        if (acc[i] == '.')
        {
            pos.w = 25;
            pos.x -= 25;
            Graphics::Instance()->DrawTexture(
                AssetManager::Instance()->GetTexture("Res/Assets/score/score-dot@2x.png"), &pos, NULL
            );
            continue;
        }
        else pos.w = 50;

        pos.x -= 30;
        Graphics::Instance()->DrawTexture(
            AssetManager::Instance()->GetTexture(path + acc[i] + "@2x.png"), &pos, NULL
        );
    }

}
