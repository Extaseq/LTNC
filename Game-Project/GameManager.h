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

    Graphics* mGraphics;

    SelectionMode* mainMenu;

    static SDL_Event mEvent;

    int BeatmapListSize;

public:

    static GameManager* Instance();

    static void Release();

    void handleKeyboard();

    void LoadBeatmap();

    void SelectionMode();

    void MainScreen();

    static std::vector<Beatmap> BeatmapList;

    bool aKeyDown = false;
    bool dKeyDown = false;

private:

    GameManager();

    ~GameManager();

};

#endif // _GAMEMANAGER_H
