#ifndef _SELECTIONMODE_H
#define _SELECTIONMODE_H

#include <SDL.h>
#include <SDL_image.h>

#include <stdio.h>
#include <vector>
#include <unordered_map>
#include <array>
#include <string>
#include <cstdlib>
#include <ctime>

#include "Graphics.h"
#include "AssetManager.h"
#include "Button.h"
#include "AudioManager.h"
#include "Beatmap/Beatmap.h"

struct Text
{
    SDL_FRect dstRect;

    SDL_Texture* texture;

    Text(const std::string& text, int x, int y, int size, bool dimmed = false)
    {
        texture = Graphics::Instance()->LoadText(text, size, dimmed);

        int w, h;

        SDL_QueryTexture(texture, NULL, NULL, &w, &h);

        dstRect = {static_cast<float>(x), static_cast<float>(y), static_cast<float>(w), static_cast<float>(h)};
    }

    void Zoom()
    {
        // dstRect.x = dstRect.x - 0.075 * dstRect.w;

        dstRect.y = dstRect.y - 0.075 * dstRect.h;

        dstRect.w *= 1.15, dstRect.h *= 1.15;
    }

    void UnZoom()
    {
        dstRect.w /= 1.15, dstRect.h /= 1.15;

        // dstRect.x = dstRect.x + 0.075 * dstRect.w;

        dstRect.y = dstRect.y + 0.075 * dstRect.h;
    }

    void Draw()
    {
        Graphics::Instance()->DrawTexture(texture, &dstRect);
    }
};

class Menu_Button : public Button
{
private:

    std::string beatmap_bg = "";

    std::vector<Text> Info;

    int index;

    SDL_FRect miniMap;

    bool Zoomed = false;

public:

    Menu_Button(int x, int y, const std::string& bg, int diffIndex, const Beatmap& beatmap)
        : Button("menu-button-background", x, y, 1968, 301, true, HOVER_TYPE_GLOW)
    {
        beatmap_bg = bg;

        index = diffIndex;

        name = "menu_button_" + std::to_string(index);

        Info.push_back(Text(beatmap.beatmapMetadata.Title, 2500, y + 20, 100));

        Info.push_back(Text(beatmap.beatmapMetadata.Artist, 2500, y + 120, 60));

        Info.push_back(Text(beatmap.beatmapDifficulty[diffIndex].difficultName, 2500, y + 220, 40));

        miniMap = {2162.0, static_cast<float>(y + 28), 320.0, 246.0};
    }

    void Zoom()
    {
        if (Zoomed == true) return;

        for (Text &T : Info) T.Zoom();

        pos->x = pos->x - 0.075 * pos->w;

        pos->y = pos->y - 0.075 * pos->h;

        pos->w *= 1.15, pos->h *= 1.15;

        miniMap = {2018, miniMap.y - 18, 320 * 1.15, 246 * 1.15};

        Zoomed = true;
    }

    void UnZoom()
    {
        if (Zoomed == false) return;

        for (Text &T : Info) T.UnZoom();

        pos->w /= 1.15, pos->h /= 1.15;

        pos->x = pos->x + pos->w * 0.075;

        pos->y = pos->y + pos->h * 0.075;

        miniMap = {2164, miniMap.y + 18, 320, 246};

        Zoomed = false;
    }

    void Render()
    {
        if (OnMouseHover()) Glow();
        Graphics::Instance()->DrawTexture(AssetManager::Instance()->GetTexture(fileName), pos);
        UnGlow();
        Graphics::Instance()->DrawTexture(AssetManager::Instance()->GetTexture(beatmap_bg), &miniMap);
        for (auto &T : Info) T.Draw();
    }
};

class SelectionMode
{
private:

    static SelectionMode* sInstance;

    std::vector<Button*> sections;

    std::vector<Menu_Button*> menu_button;

    SDL_Texture* currentArtist;

    SDL_Texture* currentTitle;

    SDL_Texture* menuButtonBackground;

    SDL_Texture* miniPic;

    std::vector<SDL_Texture*> diffList;

    std::vector<SDL_Texture*> bmInfo;

    Graphics* mGraphics;

    AssetManager* mAssetMgr;

    AudioManager* mAudioMgr;

    SDL_Texture* background;

    int prevIndex = -1, diffIndex = 0;

    Beatmap currentBeatmap;

    long long score;

public:

    static SelectionMode* Instance();

    static void Release();

    void Update(int index, int diffIndex);

    void GetScore();

    std::string getButtonClicked();

    void Render();

    void DisplayDifficulty();

private:

    SelectionMode();

    ~SelectionMode();
};

#endif // _SELECTIONMODE_H
