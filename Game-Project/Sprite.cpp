#include "Sprite.h"

Sprite::Sprite(const std::string& spriteName, int frames_)
{
    frames = frames_;

    std::string path = "Res\\" + spriteName;

    if (frames == 1)
    {
        TexList.push_back(AssetManager::Instance()->GetTexture(path + "@2x.png"));
    }
}

void Sprite::Update()
{
    // index = static_cast<int>((SDL_GetTicks() / 100) % frames);
}

void Sprite::Draw()
{
    Graphics::Instance()->DrawTexture(TexList[index], &dstRect, &srcRect);
}
