#include "PlayField.h"

PlayField::PlayField(const Beatmap& beatmap, int DiffIndex)
{
    mAssetMgr = AssetManager::Instance();
    mGraphics = Graphics::Instance();
    mAudioMgr = AudioManager::Instance();
    mInputMgr = InputManager::Instance();

    LoadBeatmap(beatmap, DiffIndex);

    playSections.push_back(new Button("taiko-bar-left", 0, 610, 510, 492 + 50));

    playSections.push_back(new Button("taiko-bar-right", 510, 616, 3840 - 510, 476 + 50));

    playSections.push_back(new Button("taikohitcircle", 605, 768 - 30, 236, 236));

    playSections.push_back(new Button("taikohitcircleoverlay", 575, 739 - 30, 296, 296));

    playSections.push_back(new Button("scorebar-bg", 0, 0, 3840, 2160));

    playSections.push_back(new Button("scorebar-colour", 14, 44, 1363, 157));

    // Pause menu
    PauseMenu = new Menu("pause-overlay");

    PauseMenu->AddButton(new Button("pause-overlay", 0, 0, 3840, 2160));

    PauseMenu->AddButton(new Button("pause-continue", 360, 285, 3109, 686, true, 2));

    PauseMenu->AddButton(new Button("pause-retry", 1342, 968, 1145, 317, true, 2));

    PauseMenu->AddButton(new Button("pause-back", 390, 1343, 3052, 556, true, 2));

    // background = mAssetMgr->GetTexture(beatmap.beatmapMetadata.BackgroundFile);

    taikoslider.texture = mAssetMgr->GetTexture("Res\\taiko-Slider@2x.png");

    while (Open() == true) {}
}

void PlayField::LoadBeatmap(const Beatmap& beatmap, int DiffIndex)
{
    // Use later
    int TimingPointIndex = 1;

    audioFile = beatmap.beatmapMetadata.AudioFileDir;

    double BaseSliderVelocity = beatmap.beatmapDifficulty[DiffIndex].SliderMultiplier;
    BaseSliderVelocity = BaseSliderVelocity * 100.0 * beatmap.beatmapInfo.BPM / 60.0;

    double SliderVelocity = BaseSliderVelocity * SPEED_RATIO; // Pixels per second


    const std::vector<HitObject>& HitObjects = beatmap.beatmapDifficulty[DiffIndex].hitObjects;
    const std::vector<TimingPoint>& TimingPoints = beatmap.beatmapDifficulty[DiffIndex].timingPoints;

    size_t TotalHitObjects = HitObjects.size();

    for (size_t index = 0; index < TotalHitObjects; ++index)
    {
        if (HitObjects[index].time == TimingPoints[TimingPointIndex].time) TimingPointIndex++;

        double appearTime = static_cast<double>(HitObjects[index].time);

        double Multiplier = 1.0;

        if (TimingPoints[TimingPointIndex - 1].uninherited == false) {
                Multiplier = (static_cast<double>(-100) / TimingPoints[TimingPointIndex - 1].beatLength);
        }

        appearTime = appearTime - ((PIXEL_TO_MOVE / (SliderVelocity * Multiplier)) * 1000); /*In miliseconds*/

        Waiting.push(HitCircle(
            HitObjects[index].type, HitObjects[index].hitSound, appearTime + 250, SliderVelocity * Multiplier
        ));
    }
}

int GetButtonOpening(const std::string& button_name)
{
    if (button_name == "pause-continue") return CONTINUE;

    if (button_name == "pause-retry") return RETRY;

    if (button_name == "pause-back") return BACK;

    return -1;
}

void PlayField::Dons(bool left)
{
    SDL_FRect dstRect = {0, 608, 254, 546};
    std::string path = "Res\\taiko-drum-inner-right@2x.png";
    if (!left)
    {
        dstRect = {254, 608, 254, 546};
        path = "Res\\taiko-drum-inner-left@2x.png";
    }

    mGraphics->DrawTexture(mAssetMgr->GetTexture(path), &dstRect, NULL, 180);
}

void PlayField::Kats(bool right)
{
    SDL_FRect dstRect = {0, 608, 254, 546};
    std::string path = "Res\\taiko-drum-outer-right@2x.png";
    if (!right)
    {
        dstRect = {254, 608, 254, 546};
        path = "Res\\taiko-drum-outer-left@2x.png";
    }

    mGraphics->DrawTexture(mAssetMgr->GetTexture(path), &dstRect, NULL, 180);
}

void PlayField::Update(int deltaTime)
{
    taikoslider.scroll(1);

    if (OnScreen.empty()) return;

    for (HitCircle& circle : OnScreen)
    {
        circle.Update(deltaTime);
    }

    while (!OnScreen.empty() && OnScreen.front().Disabled())
    {
        OnScreen.pop_front();
    }
}

void PlayField::Render()
{
    mGraphics->DrawText(taikoslider.texture, taikoslider.scrollingOffset, 0);

    mGraphics->DrawText(taikoslider.texture, taikoslider.scrollingOffset - 3840, 0);

    for (Button* section : playSections) section->Draw();

    for (const HitCircle& circle : OnScreen)
    {
        circle.Render();
    }
}

bool PlayField::Open()
{
    int HP = 100;

    bool Playing = true;

    const int frameDelay = 1000 / FPS;

    Int64 frameStart;
    int frameTime;

    int Offset = Waiting.top().GetAppearTime();
    Int64 previousTime = SDL_GetTicks();
    Int64 mStartTime = previousTime;

    if (Offset < 0) mStartTime -= Offset;

    int deltaTime = 0;

    while (Playing)
    {
        frameStart = SDL_GetTicks();

        deltaTime = frameStart - previousTime;

        if (!Waiting.empty())
        {
            if (frameStart - mStartTime >= Waiting.top().GetAppearTime())
            {
                OnScreen.push_back(Waiting.top());
                Waiting.pop();
            }
        }
        previousTime = frameStart;

        Update(deltaTime);

        if (frameStart - mStartTime >= 0)
        {
            if (Mix_PlayingMusic() != 1)
            {
                mAudioMgr->PlayMusic(audioFile);
            }
        }

        if (Waiting.empty()) if (Mix_PlayingMusic() != -1) Playing = false;

        mGraphics->ClearBackbuffer();
        Render();

        while (SDL_PollEvent(&mEvent)) {}

        if (mInputMgr->KeyPressed(SDL_SCANCODE_D)) Kats(true);
        if (mInputMgr->KeyPressed(SDL_SCANCODE_F)) Dons(true);
        if (mInputMgr->KeyPressed(SDL_SCANCODE_J)) Dons(false);
        if (mInputMgr->KeyPressed(SDL_SCANCODE_K)) Kats(false);

        if (mInputMgr->KeyPressed(SDL_SCANCODE_ESCAPE))
        {
            Mix_PauseMusic();
            int CHOICE = OpenMenu(PauseMenu);
            switch (CHOICE)
            {
                case CONTINUE:
                    break;

                case RETRY:
                    return true;
                    break;

                case BACK:
                    Mix_HaltMusic();
                    return false;

                default:
                    break;
            }
            Mix_ResumeMusic();
        }

        mGraphics->Render();

        mInputMgr->Update();

        frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime) SDL_Delay(frameDelay - frameTime);
    }

    return false;
}

int PlayField::OpenMenu(Menu* menu)
{
    const int frameDelay = 1000 / FPS;

    Uint32 frameStart;
    int frameTime;

    while (true)
    {
        frameStart = SDL_GetTicks();

        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                std::string choice = menu->GetButtonClicked();

                if (choice != "NULL") return GetButtonOpening(choice);
            }
        }

        menu->Update();

        mGraphics->ClearBackbuffer();

        menu->Draw();

        Cursor::Instance()->Render();

        mGraphics->Render();

        frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime)
        {
            SDL_Delay(frameDelay - frameTime);
        }
    }
}
