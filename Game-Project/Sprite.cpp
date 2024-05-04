#include "Sprite.h"

Sprite::Sprite(const std::string& spriteName, int frames_)
{
    frames = frames_;

    fileName = "Res\\" + spriteName + "@2x.png";
}

void Sprite::Update()
{
    SDL_GetMouseState(&Cursor::x, &Cursor::y);

    auto Texture = AssetManager::Instance()->GetTexture(fileName);

    if (Cursor::x >= 0 && Cursor::x <= 596 && Cursor::y >= 1896 && Cursor::y <= 2160)
    {
        SDL_SetTextureBlendMode(Texture, SDL_BLENDMODE_ADD);

        SDL_SetTextureAlphaMod(Texture, 1000);
    }
    else
    {
        SDL_SetTextureBlendMode(Texture, SDL_BLENDMODE_BLEND);
        SDL_SetTextureAlphaMod(Texture, 255);
    }

    // index = static_cast<int>((SDL_GetTicks() / 100) % frames);
}

void Sprite::Draw()
{
    Graphics::Instance()->DrawTexture(
        AssetManager::Instance()->GetTexture(fileName), &dstRect, &srcRect
    );
}
