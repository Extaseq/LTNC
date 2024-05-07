#include "Button.h"

Button::Button(const std::string& name_, int x, int y, int w, int h, bool _canInteract, int _interactType)
{
    AssetMgr = AssetManager::Instance();

    fileName = "Res\\" + name_ + "@2x.png";

    name = name_;

    pos = new SDL_FRect();

    *pos = {
        static_cast<float>(x),
        static_cast<float>(y),
        static_cast<float>(w),
        static_cast<float>(h)
    };

    canInteract = _canInteract;

    interactType = _interactType;
}

void Button::setSrc(int x, int y, int w, int h)
{
    clip = new SDL_Rect();

    *clip = {x, y, w, h};
}

bool Button::OnMouseHover()
{
    if (!canInteract) return false;

    int x, y;

    SDL_PumpEvents();

    SDL_GetMouseState(&x, &y);

    return ((x >= pos->x) && (x <= (pos->x + pos->w)) && (y >= pos->y) && (y <= (pos->y + pos->h)));
}

void Button::Glow()
{
    if (interacted == true) return;

    SDL_SetTextureBlendMode(AssetMgr->GetTexture(fileName), SDL_BLENDMODE_ADD);

    SDL_SetTextureAlphaMod(AssetMgr->GetTexture(fileName), static_cast<Uint8>(1000));

    interacted = true;
}

void Button::UnGlow()
{
    if (interacted == false) return;

    SDL_SetTextureBlendMode(AssetMgr->GetTexture(fileName), SDL_BLENDMODE_BLEND);

    SDL_SetTextureAlphaMod(AssetMgr->GetTexture(fileName), 255);

    interacted = false;
}

void Button::Zoom()
{
    if (interacted == true) return;

    pos->x = pos->x - 0.075 * pos->w;

    pos->y = pos->y - 0.075 * pos->h;

    pos->w *= 1.15, pos->h *= 1.15;

    interacted = true;
}

void Button::UnZoom()
{
    if (interacted == false) return;

    pos->w /= 1.15, pos->h /= 1.15;

    pos->x = pos->x + pos->w * 0.075;

    pos->y = pos->y + pos->h * 0.075;

    interacted = false;
}

void Button::Update()
{
    if (!canInteract) return;

    if (interactType == HOVER_TYPE_GLOW)
    {
        if (OnMouseHover()) Glow();
        else UnGlow();
    }

    if (interactType == HOVER_TYPE_ZOOM)
    {
        if (OnMouseHover()) Zoom();
        else UnZoom();
    }
}

void Button::Render()
{
    Graphics::Instance()->DrawTexture(AssetMgr->GetTexture(fileName), pos, clip);
}
