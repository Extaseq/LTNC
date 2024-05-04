#ifndef _MENU_H
#define _MENU_H

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
#include "UserInterface.h"
#include "AudioManager.h"
#include "Beatmap/Beatmap.h"

class SelectionMode
{
private:

    static SelectionMode* sInstance;

    /*-----------------------Name - Texture-----*/
    std::vector<std::pair<std::string, UI*>> sections;

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

public:

    static SelectionMode* Instance();

    static void Release();

    void Update(int index, int diffIndex);

    std::string getButtonClicked(int x, int y);

    void Render();

    void DisplayDifficulty();

private:

    SelectionMode();

    ~SelectionMode();
};

#endif // _MENU_H
