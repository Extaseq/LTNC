#include "Sprite.h"

Sprite::Sprite(const std::string& spriteName, int frames_)
{
    mGraphics = Graphics::Instance();

    frames = frames_;

    std::string path = "Res\\" + spriteName;

    if (frames == 1)
    {
        TexList.push_back(mGraphics->LoadTexture(path + "@2x.png"));
    }
}

void Sprite::Update()
{
    // index = static_cast<int>((SDL_GetTicks() / 100) % frames);
}

void Sprite::Draw()
{
    mGraphics->DrawTexture(TexList[index], &dstRect, &srcRect);
}
