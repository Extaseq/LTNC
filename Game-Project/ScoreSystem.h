#ifndef _SCORESYSTEM_H
#define _SCORESYSTEM_H

#include <algorithm>
#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>

#include "HitCircle.h"
#include "AssetManager.h"
#include "Graphics.h"

#define GREAT 300
#define OK 150
#define MISS 0
#define NONE -1
#define SCORE_MULTIPLIER 80

class ScoreSystem
{
private:

    static ScoreSystem* sInstance;

    long int currentScore = 0;

    int currentCombo = 0;

    double GreatTime = 0;

    double OkTime = 0;

    double MissTime = 0;

    double Accuracy = 100.0;

    int Great, Ok, Miss;

public:

    static ScoreSystem* Instance();

    void Release();

    int GetScore(double Time);

    void SetOD(double OD);

    void SetMiss();

    void UpdateAccuracy();

    void Reset();

    int GetGreat() const { return Great; }
    int GetOk() const { return Ok; }
    int GetMiss() const { return Miss; }

    int AddScore(double Time, int ClickType, HitCircle &hitCircle, bool KiaiTime = false);

    std::string _to_string(double acc);

    void Render();

private:

    ScoreSystem();

    ~ScoreSystem();
};

#endif // _SCORESYSTEM_H
