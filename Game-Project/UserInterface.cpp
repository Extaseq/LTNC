#include "UserInterface.h"
#include "GameManager.h"

bool UI::OnMouseHover(int x, int y)
{
    if (!canGlow) return false;

    return ((x >= pos->x) && (x <= (pos->x + pos->w)) && (y >= pos->y) && (y <= (pos->y + pos->h)));
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

    int x, y;

    SDL_GetMouseState(&x, &y);

    if (OnMouseHover(x, y))
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


