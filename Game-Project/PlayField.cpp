#include "PlayField.h"

Int64 mStartTime;

PlayField::PlayField(const Beatmap& beatmap, int DiffIndex, bool AutoPlay)
{
    mAssetMgr = AssetManager::Instance();
    mGraphics = Graphics::Instance();
    mAudioMgr = AudioManager::Instance();
    mInputMgr = InputManager::Instance();
    mScore = ScoreSystem::Instance();
    mTimer = Timer::Instance();
    mHPBar = new HPBar();

    Mix_AllocateChannels(100);

    Auto = AutoPlay;

    LoadBeatmap(beatmap, DiffIndex);

    playSections.push_back(new Button("taiko-bar-left", 0, 610, 510, 492 + 50));
    playSections.push_back(new Button("taiko-bar-right", 510, 616, 3840 - 510, 476 + 50));
    playSections.push_back(new Button("taikohitcircle", 605, 768 - 30, 236, 236));
    playSections.push_back(new Button("taikohitcircleoverlay", 575, 739 - 30, 296, 296));
    playSections.push_back(new Button("scorebar-bg", 0, 0, 3840, 2160));
    // playSections.push_back(new Button("scorebar-colour", 14, 44, 1363, 157));

    // Pause menu
    PauseMenu = new Menu("Res/pause-overlay@2x.png");
    PauseMenu->AddButton(new Button("pause-continue", 360, 285, 3109, 686, true, 2));
    PauseMenu->AddButton(new Button("pause-retry", 1342, 968, 1145, 317, true, 2));
    PauseMenu->AddButton(new Button("pause-back", 390, 1343, 3052, 556, true, 2));

    // background = mAssetMgr->GetTexture(beatmap.beatmapMetadata.BackgroundFile);

    // Fail menu
    FailMenu = new Menu("Res/fail-background@2x.png");
    FailMenu->AddButton(new Button("pause-retry", 1342, 968, 1145, 317, true, 2));
    FailMenu->AddButton(new Button("pause-back", 390, 1343, 3052, 556, true, 2));

    taikoslider.texture = mAssetMgr->GetTexture("Res\\taiko-Slider@2x.png");

    auto SavePoint = Waiting;

    if (AutoPlay == true) OpenAutoPlay();
    else
    {
        while (Open() == true)
        {
            Waiting = SavePoint;
            OnScreen.clear();
        }
    }

    if (!failed)
    {
        Mix_HaltMusic();
        mAudioMgr->PlayMusic("Res/applause.ogg");
        ScoreBoard = new RankingPanel(mScore, SavePoint.size());
        ScoreBoard->SetInfo(
            beatmap.beatmapMetadata.Artist,
            beatmap.beatmapMetadata.Title,
            beatmap.beatmapDifficulty[DiffIndex].difficultName
        );

        ScoreBoard->Open();

        if (!AutoPlay) mScore->UpdateOverallScore();
    }
}

void PlayField::LoadBeatmap(const Beatmap& beatmap, int DiffIndex)
{
    int TimingPointIndex = 1;

    DrainRate = beatmap.beatmapDifficulty[DiffIndex].DrainRate;

    mScore->SetOD(beatmap.beatmapDifficulty[DiffIndex].OverallDifficulty);

    audioFile = beatmap.beatmapMetadata.AudioFileDir;

    double BaseSliderVelocity = beatmap.beatmapDifficulty[DiffIndex].SliderMultiplier;
    BaseSliderVelocity = BaseSliderVelocity * 100.0 * beatmap.beatmapInfo.BPM / 60.0;

    double SliderVelocity = BaseSliderVelocity * SPEED_RATIO; // Pixels per second

    const std::vector<HitObject>& HitObjects = beatmap.beatmapDifficulty[DiffIndex].hitObjects;
    const std::vector<TimingPoint>& TimingPoints = beatmap.beatmapDifficulty[DiffIndex].timingPoints;

    size_t TotalHitObjects = HitObjects.size();

    for (size_t index = 0; index < TotalHitObjects; ++index)
    {
        if (HitObjects[index].time >= TimingPoints[TimingPointIndex].time) TimingPointIndex++;

        if (TimingPointIndex > (int)TimingPoints.size()) TimingPointIndex = (int)TimingPoints.size();

        double Multiplier = 1.0;

        if (TimingPoints[TimingPointIndex - 1].uninherited == false) {
                Multiplier = (static_cast<double>(-100) / TimingPoints[TimingPointIndex - 1].beatLength);
        }

        Waiting.push(HitCircle(
            HitObjects[index].hitSound, HitObjects[index].time, SliderVelocity * Multiplier
        ));
    }
}

int PlayField::GetButtonOpening(const std::string& button_name)
{
    if (button_name == "pause-continue")
    {
        mAudioMgr->PlaySFX("Res/pause-continue-click.ogg");
        return CONTINUE;
    }

    if (button_name == "pause-retry")
    {
        mAudioMgr->PlaySFX("Res/pause-retry-click.ogg");
        return RETRY;
    }

    if (button_name == "pause-back")
    {
        mAudioMgr->PlaySFX("Res/pause-back-click.ogg");
        return BACK;
    }

    return -1;
}

void PlayField::Dons(bool left, Int64 Time)
{
    SDL_FRect dstRect = {0, 608, 254, 546};
    std::string path = "Res\\taiko-drum-inner-right@2x.png";
    if (!left)
    {
        dstRect = {254, 608, 254, 546};
        path = "Res\\taiko-drum-inner-left@2x.png";
    }

    PlayButton(Time, DONS);

    mGraphics->DrawTexture(mAssetMgr->GetTexture(path), &dstRect, NULL, 180);
}

void PlayField::Kats(bool right, Int64 Time)
{
    SDL_FRect dstRect = {0, 608, 254, 546};
    std::string path = "Res\\taiko-drum-outer-right@2x.png";
    if (!right)
    {
        dstRect = {254, 608, 254, 546};
        path = "Res\\taiko-drum-outer-left@2x.png";
    }

    PlayButton(Time, KATS);

    mGraphics->DrawTexture(mAssetMgr->GetTexture(path), &dstRect, NULL, 180);
}

void PlayField::PlayButton(Int64 Time, int Type)
{
    if (OnScreen.empty()) return;

    Time = Time - OnScreen.front().GetTime();
    int Score = mScore->AddScore(Time, Type, OnScreen.front(), false);
    SDL_FRect dst = {475, 606, 520, 520};

    switch (Score)
    {
        case GREAT:
            mGraphics->DrawTexture(mAssetMgr->GetTexture("Res/taiko-hit300@2x.png"), &dst, NULL);
            CurrentHP += DrainRate;
            break;

        case OK:
            mGraphics->DrawTexture(mAssetMgr->GetTexture("Res/taiko-hit100@2x.png"), &dst, NULL);
            CurrentHP += (0.5 * DrainRate);
            break;

        case MISS:
            mGraphics->DrawTexture(mAssetMgr->GetTexture("Res/taiko-hit0@2x.png"), &dst, NULL);
            CurrentHP -= DrainRate;
            break;

        default:
            break;
    }
}

void PlayField::Update(int deltaTime)
{
    taikoslider.scroll(1);

    mHPBar->Update(CurrentHP);

    if (OnScreen.empty()) return;

    for (HitCircle& circle : OnScreen) circle.Update(deltaTime);
}

void PlayField::Render()
{
    mGraphics->DrawText(taikoslider.texture, taikoslider.scrollingOffset, 0);

    mGraphics->DrawText(taikoslider.texture, taikoslider.scrollingOffset - 3840, 0);

    for (Button* section : playSections) section->Draw();

    mHPBar->Draw();

    for (const HitCircle& circle : OnScreen)
    {
        circle.Render();
    }

    if (!Auto)
    {
        if (!OnScreen.empty() && OnScreen.front().Disabled())
        {
            if (!OnScreen.front().GetClicked())
            {
                SDL_FRect dst = {440, 606, 476, 476};
                mGraphics->DrawTexture(mAssetMgr->GetTexture("Res/taiko-hit0@2x.png"), &dst, NULL);
                CurrentHP -= DrainRate;
                mScore->SetMiss();
            }
        }

        while (!OnScreen.empty() && OnScreen.front().Disabled())
        {
            OnScreen.pop_front();
        }
    }

    if (Waiting.empty() && OnScreen.empty()) Playing = false;
}

bool PlayField::Open()
{
    CurrentHP = MAX_HP;

    Playing = true;

    Int64 frameStart;
    int Offset = Waiting.top().GetAppearTime();
    Int64 previousTime = mTimer->Now();
    mStartTime = previousTime;

    if (RetryOffset != 0)
    {
        mStartTime += RetryOffset;
        RetryOffset = 0;
    }

    if (Offset < 0) mStartTime -= Offset;
    Offset = 0;

    int deltaTime = 0;

    mScore->Reset();

    while (Playing)
    {
        frameStart = mTimer->Now();

        deltaTime = frameStart - previousTime;
        if (LastMenuOpened)
        {
            deltaTime -= Offset;
            mStartTime += Offset;
            LastMenuOpened = false;
        }

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

        mGraphics->ClearBackbuffer();
        Render();

        while (SDL_PollEvent(&mEvent)) {}

        if (mInputMgr->KeyPressed(SDL_SCANCODE_D))
        {
            Kats(true, mTimer->Now() - mStartTime);
        }
        if (mInputMgr->KeyPressed(SDL_SCANCODE_F))
        {
            Dons(true, mTimer->Now() - mStartTime);
        }
        if (mInputMgr->KeyPressed(SDL_SCANCODE_J))
        {
            Dons(false, mTimer->Now() - mStartTime);
        }
        if (mInputMgr->KeyPressed(SDL_SCANCODE_K))
        {
            Kats(false, mTimer->Now() - mStartTime);
        }

        if (mInputMgr->KeyPressed(SDL_SCANCODE_ESCAPE))
        {
            Mix_PauseMusic();
            mAudioMgr->PlayMusic("Res/applause.ogg");
            int CHOICE = OpenMenu(PauseMenu);
            switch (CHOICE)
            {
                case CONTINUE:
                    LastMenuOpened = true;
                    break;

                case RETRY:
                    RetryOffset = mTimer->Now() - frameStart;
                    Mix_HaltMusic();
                    return true;
                    break;

                case BACK:
                    Mix_HaltMusic();
                    failed = true;
                    return false;

                default:
                    break;
            }
            Offset = mTimer->Now() - frameStart;
            Mix_ResumeMusic();
        }

        if (CurrentHP <= 0)
        {
            Mix_HaltMusic();
            mAudioMgr->PlayMusic("Res/failsound.ogg");
            int CHOICE = OpenMenu(FailMenu);
            switch (CHOICE)
            {
                case RETRY:
                    RetryOffset = mTimer->Now() - frameStart;
                    return true;
                    break;

                case BACK:
                    failed = true;
                    return false;
            }
        }

        mScore->Render();

        mGraphics->Render();

        mInputMgr->Update();
    }

    return false;
}

void PlayField::OpenAutoPlay()
{
    CurrentHP = MAX_HP;

    Playing = true;

    failed = false;

    Int64 frameStart;
    int Offset = Waiting.top().GetAppearTime();
    Int64 previousTime = mTimer->Now();
    mStartTime = previousTime;

    if (Offset < 0) mStartTime -= Offset;
    Offset = 0;

    int deltaTime = 0;

    mScore->Reset();

    while (Playing)
    {
        frameStart = mTimer->Now();

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

        mGraphics->ClearBackbuffer();

        Render();

        if (!OnScreen.empty())
        {
            int Time = mTimer->Now() - mStartTime;
            if (Time >= OnScreen.front().GetTime())
            {
                if (OnScreen.front().GetType() == KATS)
                {
                    Kats(true, OnScreen.front().GetTime());
                }
                if (OnScreen.front().GetType() == DONS)
                {
                    Dons(true, OnScreen.front().GetTime());
                }
                OnScreen.pop_front();
            }
        }

        while (SDL_PollEvent(&mEvent)) {}

        if (mInputMgr->KeyPressed(SDL_SCANCODE_ESCAPE))
        {
            Mix_PauseMusic();
            failed = true;
            return;
        }

        mScore->Render();

        mGraphics->Render();

        mInputMgr->Update();
    }
}

int PlayField::OpenMenu(Menu* menu)
{
    const int frameDelay = 1000 / 60;

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
