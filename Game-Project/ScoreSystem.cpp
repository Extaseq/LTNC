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
    if (Time <= Great) return GREAT;
    if (Time <= Ok) return OK;
    return MISS;
}

void ScoreSystem::SetOD(double OD)
{
    Great = 50 - 3 * OD;

    if (OD < 5)
    {
        Ok = 120 - 8 * OD;
        Miss = 135 - 8 * OD;
    }
    else
    {
        Ok = 110 - 6 * OD;
        Miss = 120 - 5 * OD;
    }

    currentCombo = 0;

    currentScore = 0;
}

bool ScoreSystem::Update(double Time, int ClickType, int CircleType, bool KiaiTime)
{
    Time = std::abs(Time);

    if (Time > Miss) return false;

    if (ClickType != CircleType)
    {
        currentCombo = 0;
        return false;
    }

    int Score = GetScore(Time);

    if (Score == MISS)
    {
        currentCombo = 0;
        return false;
    }

    currentCombo++;

    currentScore += (
        (Score + std::min(currentCombo / 10, 10) * SCORE_MULTIPLIER) * (KiaiTime ? 1.2 : 1)
    );

    std::cout << Time << " " << ClickType << " " << CircleType << ": ";
    std::cout << currentCombo << " " << currentScore << "\n";

    return true;
}

void ScoreSystem::Render()
{
    printf("%d %ld\n", currentCombo, currentScore);
}
