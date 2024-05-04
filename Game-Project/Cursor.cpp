#include "Cursor.h"

Cursor* Cursor::sInstance = nullptr;

Cursor* Cursor::Instance()
{
    if (sInstance == nullptr)
    {
        sInstance = new Cursor();
    }
    return sInstance;
}

void Cursor::Release()
{
    delete sInstance;
    sInstance = nullptr;
}

void Cursor::Update()
{
    SDL_GetMouseState(&x, &y);

    angle += PI / 6;

    RenderQuad = {x - 256 / 2, y - 256 / 2, 256, 256};
}

void Cursor::Render()
{
    Update();

    Graphics::Instance()->DrawTexture(cursor, &RenderQuad, NULL, angle);
}

Cursor::Cursor()
{
    cursor = AssetManager::Instance()->GetTexture("Res\\cursor@2x.png");
}

Cursor::~Cursor()
{

}
