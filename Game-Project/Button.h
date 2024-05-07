#ifndef _BUTTON_H
#define _BUTTON_H

#include "AssetManager.h"

#define HOVER_TYPE_GLOW 1
#define HOVER_TYPE_ZOOM 2

class Button
{
protected:

    SDL_FRect* pos = NULL;

    SDL_Rect* clip = NULL;

    std::string fileName;

    std::string name;

    AssetManager* AssetMgr;

    bool interacted = false;

    bool canInteract = false;

    int interactType = 1;

public:

    Button() = default;

    Button(const std::string& name_, int x, int y, int w, int h, bool _canInteract = false, int _interactType = 1);

    void setSrc(int x, int y, int w, int h);

    void Glow();

    void UnGlow();

    void Zoom();

    void UnZoom();

    bool OnMouseHover();

    void Update();

    void Draw();

    std::string GetName()
    {
        return name;
    }
};

#endif // _BUTTON_H
