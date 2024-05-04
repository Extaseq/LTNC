#ifndef _MENU_H
#define _MENU_H

#include <SDL.h>
#include <SDL_image.h>

#include <stdio.h>
#include <vector>
#include <unordered_map>
#include <array>

#include "Graphics.h"
#include "UserInterface.h"
#include "AudioManager.h"
#include "Beatmap/Beatmap.h"

class SelectionMode
{
private:

    static SelectionMode* sInstance;

    /*-----------------------Name - Texture-----*/
    std::vector<std::pair<std::string, UI*>> sections;

    std::vector<UI*> difficultyList;

    std::vector<SDL_Texture*> bmInfo;

    Graphics* mGraphics;

    AudioManager* mAudioMgr;

    SDL_Texture* background;

    int prevIndex = -1;

    Beatmap currentBeatmap;

public:

    static SelectionMode* Instance();

    static void Release();

    void Update(int index);

    std::string getButtonClicked(int x, int y);

    void Render();

private:

    SelectionMode();

    ~SelectionMode();
};

#endif // _MENU_H
