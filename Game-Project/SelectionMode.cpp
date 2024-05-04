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

    mAssetMgr = AssetManager::Instance();

    sections.push_back(UI::make_pair("songselect-top", 0, -1, 3652, 1336, false));

    sections.push_back(UI::make_pair("songselect-bottom", 0, 1761, 3840, 399, false));

    sections.push_back(UI::make_pair("selection-mode", 632.0, -1.0, 3208.0, 2161.0, false));
    sections.back().second->setSrc(0, 68, 2284, 1542);

    sections.push_back(UI::make_pair("selection-random-over", 1106, 1939, 259, 221, true));

    sections.push_back(UI::make_pair("menu-back", 0, 1896, 596, 264, true));

    menuButtonBackground = mAssetMgr->GetTexture("Res\\menu-button-background@2x.png");
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

void SelectionMode::DisplayDifficulty()
{
    int nDiff = static_cast<int>(currentBeatmap.beatmapDifficulty.size());

    int gap = 1505 / nDiff;

    int yPosStart = 350; // x = 2140

    double scale;

    for (int i = 0; i < nDiff; ++i)
    {
        if (i == diffIndex) scale = 1.1;
        else scale = 1;

        yPosStart = 350 + i * gap + gap / 2 - 301 / 2;

        SDL_FRect dstRect = {2140, yPosStart, 1968 * scale, 301 * scale};

        mGraphics->DrawTexture(menuButtonBackground, &dstRect);

        SDL_FRect mini = {2164, yPosStart + 34, 320 * scale, 240 * scale};

        mGraphics->DrawTexture(background, &mini);

        mGraphics->DrawText(currentTitle, 2500 + (scale - 1) * 300, yPosStart + 20);

        mGraphics->DrawText(currentArtist, 2500 + (scale - 1) * 300, yPosStart + 120);

        mGraphics->DrawText(diffList[i], 2500 + (scale - 1) * 300, yPosStart + 220);
    }
}

void SelectionMode::Update(int beatmapIndex, int diffIndex_)
{
    diffIndex = diffIndex_;

    for (std::pair<std::string, UI*> section : sections)
    {
        section.second->Update();
    }

    if (prevIndex == beatmapIndex) return;

    bmInfo.clear();

    diffList.clear();

    background = mAssetMgr->GetTexture(GameManager::BeatmapList[beatmapIndex].beatmapMetadata.BackgroundFile);

    currentBeatmap = GameManager::BeatmapList[beatmapIndex];

    bmInfo.push_back(mGraphics->LoadText(
        "(" + currentBeatmap.beatmapMetadata.Artist + ") - " + currentBeatmap.beatmapMetadata.Title, 50)
    );

    float time = Mix_MusicDuration(AssetManager::Instance()->getMusic(currentBeatmap.beatmapMetadata.AudioFileDir));

    bmInfo.push_back(mGraphics->LoadText(
        "Length: " + Parsing::secondsToTimeString(time) + "  BPM: " + std::to_string(currentBeatmap.beatmapInfo.BPM), 40
    ));

    if (Mix_PlayingMusic() != 1)
    {
        mAudioMgr->PlayMusic(currentBeatmap.beatmapMetadata.AudioFileDir);

        Mix_SetMusicPosition(static_cast<float>(currentBeatmap.beatmapMetadata.PreviewTime / 1000.0));
    }

    currentArtist = mGraphics->LoadText(currentBeatmap.beatmapMetadata.Artist, 60);

    currentTitle = mGraphics->LoadText(currentBeatmap.beatmapMetadata.Title, 100);

    for (BeatmapDifficulty diff : currentBeatmap.beatmapDifficulty)
    {
        diffList.push_back(
            mGraphics->LoadText(diff.difficultName, 40)
        );
    }

    prevIndex = beatmapIndex;
}

void SelectionMode::Render()
{
    mGraphics->DrawTexture(background, NULL, NULL);

    DisplayDifficulty();

    for (std::pair<std::string, UI*> section : sections)
    {
        section.second->Render();
    }

    sections.back().second->Render();

    mGraphics->DrawText(bmInfo[0], 200, 10);
    mGraphics->DrawText(bmInfo[1], 200, 80);
}
