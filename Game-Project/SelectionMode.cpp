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

SelectionMode::SelectionMode()
{
    mGraphics = Graphics::Instance();

    sections.push_back(UI::make_pair("songselect-top", 0, 0, 3652, 1335, false));

    sections.push_back(UI::make_pair("songselect-bottom", 0, 1761, 3840, 399, false));

    sections.push_back(UI::make_pair("selection-mode", 632.0, -1.0, 3208.0, 2161.0, false));
    sections.back().second->setSrc(0, 68, 2284, 1542);

    sections.push_back(UI::make_pair("menu-back", 0, 1896, 596, 264, true));
}

SelectionMode::~SelectionMode()
{

}

void SelectionMode::Update(int index)
{
    for (std::pair<std::string, UI*> section : sections)
    {
        section.second->Update();
    }

    if (prevIndex == index) return;

    background = mGraphics->LoadTexture(GameManager::BeatmapList[index].beatmapMetadata.BackgroundFile);

    prevIndex = index;
}

void SelectionMode::Render()
{
    mGraphics->DrawTexture(background, NULL, NULL);

    for (std::pair<std::string, UI*> section : sections)
    {
        section.second->Render();
    }
}
