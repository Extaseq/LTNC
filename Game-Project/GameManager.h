#ifndef _GAMEMANAGER_H
#define _GAMEMANAGER_H

#include "Graphics.h"
#include "Cursor.h"
#include "SelectionMode.h"
#include "Beatmap/Formats/Decoder.h"

#include <dirent.h>

class GameManager
{
private:

    static GameManager* sInstance;

    const int FPS = 60;

    const std::string BEATMAP_FOLDER = "Songs";

    bool mQuit;

    SDL_Texture* mainScreen;

    SDL_Texture* clickToPlay;

    Graphics* mGraphics;

    AudioManager* mAudioMgr;

    SelectionMode* mainMenu;

    int BeatmapListSize;

public:

    static GameManager* Instance();

    static SDL_Event mEvent;

    static void Release();

    void handleKeyboard();

    void LoadBeatmap();

    void SelectionMode();

    void MainScreen();

    void FadeIn();

    static std::vector<Beatmap> BeatmapList;

    bool aKeyDown = false;

    bool dKeyDown = false;

    bool wKeyDown = false;

    bool sKeyDown = false;

private:

    GameManager();

    ~GameManager();

};

#endif // _GAMEMANAGER_H
