#include "UserInterface.h"

bool UI::OnMouseHover()
{
    SDL_GetMouseState(&x, &y);

    return ((x >= pos->x) && (x <= (pos->w + pos->x)) && (y >= pos->y) && (y <= (pos->y + pos->h)));

}

void UI::Glow()
{
    if (glow == true) return;

    SDL_SetTextureBlendMode(AssetMgr->GetTexture(fileName), SDL_BLENDMODE_ADD);

    SDL_SetTextureAlphaMod(AssetMgr->GetTexture(fileName), 1000);

    glow = true;
}

void UI::UnGlow()
{
    if (glow == false) return;

    SDL_SetTextureBlendMode(AssetMgr->GetTexture(fileName), SDL_BLENDMODE_BLEND);

    SDL_SetTextureAlphaMod(AssetMgr->GetTexture(fileName), 255);

    glow = false;
}

void UI::Update()
{
    if (!canGlow) return;

    if (OnMouseHover())
    {
        Glow();
    }
    else
    {
        UnGlow();
    }
}

void UI::Render()
{
    Graphics::Instance()->DrawTexture(AssetMgr->GetTexture(fileName), pos, clip);
}


