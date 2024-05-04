#ifndef _USERINTERFACE_H
#define _USERINTERFACE_H

#include "AssetManager.h"

class UI
{
private:

    SDL_FRect* pos = NULL;

    SDL_Rect* clip = NULL;

    std::string fileName;

    AssetManager* AssetMgr;

    int scale = 1;

    int x, y;

    bool glow = false;

    bool canGlow = false;

public:

    UI(const std::string name, int x, int y, int w, int h, bool gl)
    {
        AssetMgr = AssetManager::Instance();

        fileName = "Res\\" + name + "@2x.png";

        pos = new SDL_FRect();

        *pos = {x, y, w, h};

        canGlow = gl;
    }

    void setSrc(int x, int y, int w, int h)
    {
        clip = new SDL_Rect();

        *clip = {x, y, w, h};
    }

    void setScale(int sc)
    {
        this->scale = sc;
    }

    void Glow();

    void UnGlow();

    bool OnMouseHover();

    void Update();

    void Render();

    static std::pair<std::string, UI*> make_pair(std::string name, int x, int y, int w, int h, bool gl)
    {
        return std::make_pair(name, new UI(name, x, y, w, h, gl));
    }
};

#endif // _USERINTERFACE_H
