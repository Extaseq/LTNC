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
    delete sInstance;
    sInstance = nullptr;
}

SelectionMode::SelectionMode()
{
    mGraphics = Graphics::Instance();

    mAudioMgr = AudioManager::Instance();

    mAssetMgr = AssetManager::Instance();

    sections.push_back(new Button("songselect-top", 0, -1, 3652, 1336));

    sections.push_back(new Button("songselect-bottom", 0, 1761, 3840, 399));

    sections.push_back(new Button("selection-mode", 632.0, -1.0, 3208.0, 2161.0));
    sections.back()->setSrc(0, 68, 2284, 1542);

    sections.push_back(new Button("selection-random-over", 1106, 1939, 259, 221, true, HOVER_TYPE_GLOW));

    sections.push_back(new Button("selection-mods-over", 888, 1939, 221, 221, true, HOVER_TYPE_GLOW));

    sections.push_back(new Button("menu-back", 0, 1896, 596, 264, true, HOVER_TYPE_GLOW));

    menuButtonBackground = mAssetMgr->GetTexture("Res\\menu-button-background@2x.png");
}

SelectionMode::~SelectionMode()
{
    for (SDL_Texture* texture : diffList)
    {
        SDL_DestroyTexture(texture);
    }

    for (SDL_Texture* texture : bmInfo)
    {
        SDL_DestroyTexture(texture);
    }
}

std::string SelectionMode::getButtonClicked()
{
    for (auto section : sections)
    {
        if (section->OnMouseHover())
        {
            return section->GetName();
        }
    }

    for (auto button : menu_button)
    {
        if (button->OnMouseHover())
        {
            return button->GetName();
        }
    }

    return "NULL";
}

void SelectionMode::Update(int beatmapIndex, int diffIndex_)
{
    diffIndex = diffIndex_;

    for (Button* section : sections)
    {
        section->Update();
    }

    for (int index = 0; index < (int)menu_button.size(); ++index)
    {
        if (index == diffIndex)
        {
            menu_button[index]->Zoom();
        }
        else
        {
            menu_button[index]->UnZoom();
        }
    }

    // Avoid updating too much
    if (prevIndex == beatmapIndex) return;

    bmInfo.clear();

    diffList.clear();

    menu_button.clear();

    background = mAssetMgr->GetTexture(GameManager::BeatmapList[beatmapIndex].beatmapMetadata.BackgroundFile);

    currentBeatmap = GameManager::BeatmapList[beatmapIndex];

    bmInfo.push_back(mGraphics->LoadText(
        "(" + currentBeatmap.beatmapMetadata.Artist + ") - " + currentBeatmap.beatmapMetadata.Title, 50)
    );

    float time = Mix_MusicDuration(AssetManager::Instance()->GetMusic(currentBeatmap.beatmapMetadata.AudioFileDir));

    bmInfo.push_back(mGraphics->LoadText(
        "Length: " + Parsing::secondsToTimeString(time) + "  BPM: " + std::to_string(currentBeatmap.beatmapInfo.BPM), 40
    ));

    currentArtist = mGraphics->LoadText(currentBeatmap.beatmapMetadata.Artist, 60);

    currentTitle = mGraphics->LoadText(currentBeatmap.beatmapMetadata.Title, 100);

    for (BeatmapDifficulty diff : currentBeatmap.beatmapDifficulty)
    {
        diffList.push_back(
            mGraphics->LoadText(diff.difficultName, 40)
        );
    }

    // From here
    int nDiff = static_cast<int>(currentBeatmap.beatmapDifficulty.size());

    double gap = 1505 / nDiff;

    for (int i = 0; i < nDiff; ++i)
    {
        menu_button.push_back(new Menu_Button(2140, 350 + i * gap + gap / 2 - 301 / 2, currentBeatmap.beatmapMetadata.BackgroundFile, i, currentBeatmap));
    }
    // To here

    prevIndex = beatmapIndex;
}

void SelectionMode::Render()
{
    if (Mix_PlayingMusic() != 1)
    {
        mAudioMgr->PlayMusic(currentBeatmap.beatmapMetadata.AudioFileDir);

        Mix_SetMusicPosition(static_cast<float>(currentBeatmap.beatmapMetadata.PreviewTime / 1000.0));
    }

    mGraphics->DrawTexture(background, NULL, NULL);

    for (Menu_Button* button : menu_button) button->Render();

    for (Button* section : sections)
    {
        section->Draw();
    }

    // sections.back()->Draw();

    mGraphics->DrawText(bmInfo[0], 200, 10);
    mGraphics->DrawText(bmInfo[1], 200, 80);
}
