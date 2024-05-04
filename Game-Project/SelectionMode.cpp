#include "SelectionMode.h"
#include "GameManager.h"

SelectionMode* SelectionMode::sInstance = nullptr;

SelectionMode* SelectionMode::Instance()
{
    if (sInstance == nullptr)
    {
        sInstance = new SelectionMode();
    }
    return sInstance;
}

void SelectionMode::Release()
{

}

// Constructor
SelectionMode::SelectionMode()
{
    mGraphics = Graphics::Instance();

    UI.push_back(new Sprite("songselect-top", 1));
    UI.back()->dstRect = {0, 0, 3652.0, 1335.0};
    UI.back()->srcRect = {0, 0, 2599, 950};

    UI.push_back(new Sprite("songselect-bottom", 1));
    UI.back()->dstRect = {0, 1761.0, 3840, 399.0};
    UI.back()->srcRect = {0, 0, 2732, 284};

    UI.push_back(new Sprite("selection-mode", 1));
    UI.back()->dstRect = {632.0, -1.0, 3208.0, 2161.0};
    UI.back()->srcRect = {0, 68, 2284, 1542};

    UI.push_back(new Sprite("menu-back", 1));
    UI.back()->dstRect = {0, 1896, 596, 264};
    UI.back()->srcRect = {0, 0, 427, 189};
}

SelectionMode::~SelectionMode()
{

}

void SelectionMode::Update(int index)
{
    if (prevIndex == index) return;

    background = mGraphics->LoadTexture(GameManager::BeatmapList[index].beatmapMetadata.BackgroundFile);

    for (Sprite* section : UI)
    {
        section->Update();
    }

    prevIndex = index;
}

void SelectionMode::Render()
{
    mGraphics->DrawTexture(background, NULL, NULL);

    for (Sprite* section : UI)
    {
        section->Draw();
    }
}
