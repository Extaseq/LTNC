#ifndef _SCORESYSTEM_H
#define _SCORESYSTEM_H

#include <algorithm>
#include <iostream>

#define GREAT 300
#define OK 150
#define MISS 0
#define SCORE_MULTIPLIER 64

class ScoreSystem
{
private:

    static ScoreSystem* sInstance;

    long int currentScore = 0;

    int currentCombo = 0;

    double Great = 0;

    double Ok = 0;

    double Miss = 0;

public:

    static ScoreSystem* Instance();

    void Release();

    int GetScore(double Time);

    void SetOD(double OD);

    bool Update(double Time, int ClickType, int CircleType, bool KiaiTime = false);

    void Render();

private:

    ScoreSystem();

    ~ScoreSystem();
};

#endif // _SCORESYSTEM_H
