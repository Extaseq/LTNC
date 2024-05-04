#include "SelectionMode.h"
#include "GameManager.h"

#include <iostream>

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

    mAudioMgr = AudioManager::Instance();

    sections.push_back(UI::make_pair("songselect-top", 0, -1, 3652, 1336, false));

    sections.push_back(UI::make_pair("songselect-bottom", 0, 1761, 3840, 399, false));

    sections.push_back(UI::make_pair("selection-mode", 632.0, -1.0, 3208.0, 2161.0, false));
    sections.back().second->setSrc(0, 68, 2284, 1542);

    sections.push_back(UI::make_pair("menu-back", 0, 1896, 596, 264, true));
}

SelectionMode::~SelectionMode()
{

}

std::string SelectionMode::getButtonClicked(int x, int y)
{
    for (auto section : sections)
    {
        if (section.second->OnMouseHover(x, y))
        {
            return section.second->getName();
        }
    }

    return "NULL";
}

void SelectionMode::Update(int beatmapIndex)
{
    for (std::pair<std::string, UI*> section : sections)
    {
        section.second->Update();
    }

    if (prevIndex == beatmapIndex) return;

    bmInfo.clear();

    background = mGraphics->LoadTexture(GameManager::BeatmapList[beatmapIndex].beatmapMetadata.BackgroundFile);

    currentBeatmap = GameManager::BeatmapList[beatmapIndex];

    bmInfo.push_back(mGraphics->LoadText(
        "(" + currentBeatmap.beatmapMetadata.Artist + ") - " + currentBeatmap.beatmapMetadata.Title, 50)
    );

    if (Mix_PlayingMusic() != 1)
    {
        mAudioMgr->PlayMusic(currentBeatmap.beatmapMetadata.AudioFileDir.c_str());
    }

    prevIndex = beatmapIndex;
}

void SelectionMode::Render()
{
    mGraphics->DrawTexture(background, NULL, NULL);

    for (std::pair<std::string, UI*> section : sections)
    {
        section.second->Render();
    }

    mGraphics->DrawText(bmInfo[0], 200, 10);
}
