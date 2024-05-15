#ifndef _HITCIRCLE_H
#define _HITCIRCLE_H

#include "Graphics.h"
#include "AssetManager.h"
#include "AudioManager.h"

#include <string>
#include <vector>

#define SPEED_RATIO 7.5 /*For 3840x2160 screen ratio*/
#define PIXEL_TO_MOVE 3300
#define KATS 1
#define DONS 0

class HitCircle
{
private:

    std::string dir = "";

    SDL_FRect Pos = {3840, 735, 248, 248};

    double Velocity = 0.0;

    double AppearTime = -1.0;

    double Time = 0;

    bool BigSize = false;

    bool Disable = false;

    bool Clicked = false;

    int Type = DONS;

public:

    HitCircle() = default;

    HitCircle(int Hitsound, double Time_, double velocity_) : Velocity(velocity_), Time(Time_)
    {
        if (Hitsound & (1 << 0)) dir = "Res/red-";

        if (Hitsound & (1 << 1))
        {
            dir = "Res/blue-";
            Type = KATS;
        }
        if (Hitsound & (1 << 3))
        {
            dir = "Res/blue-";
            Type = KATS;
        }
        if (Hitsound & (1 << 2))
        {
            if (dir == "") dir = "Res/red-";
            else Type = KATS;
            dir += "bigcircle.png";
            BigSize = true;
            Pos = {3840, 673, 376, 376};
            AppearTime = Time_ - 3238.0 / velocity_ * 1000 + 15;
        }
        else
        {
            if (dir == "") dir = "Res/red-";
            else Type = KATS;
            dir += "hitcircle.png";
            AppearTime = Time_ - 3300 / velocity_ * 1000 + 15;
        }

        this->Velocity /= 1000;
    }

    void SetClicked() { this->Clicked = true;}

    bool GetClicked() { return this->Clicked; }

    int GetType() const { return Type; }

    int GetTime() const { return Time; }

    bool Disabled() const { return Disable; }

    void SetDisabled() { this->Disable = true; }

    double GetAppearTime() const { return AppearTime; }

    void Update(int deltaTime)
    {
        Pos.x -= Velocity * deltaTime; // Delta time in miliseconds
        if (BigSize)
            Disable = (Pos.x <= 540);
        else Disable = (Pos.x <= 602);
    }

    void Render() const
    {
        if (BigSize) if (Pos.x <= 540) return;

        if (!BigSize) if (Pos.x <= 620) return;

        Graphics::Instance()->DrawTexture(
            AssetManager::Instance()->GetTexture(dir), &Pos, NULL
        );
    }

    bool operator<(const HitCircle& other) const
    {
        return this->GetAppearTime() > other.GetAppearTime();
    }

    bool operator>(const HitCircle& other) const
    {
        return this->GetAppearTime() < other.GetAppearTime();
    }
};

struct HitCircleComparator {
    bool operator()(const HitCircle& a, const HitCircle& b) const {
        return a.GetAppearTime() > b.GetAppearTime();
    }
};

#endif // _HITCIRCLE_H
