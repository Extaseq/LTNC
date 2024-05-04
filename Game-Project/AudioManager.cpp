#include "AudioManager.h"

AudioManager* AudioManager::sInstance = nullptr;

AudioManager* AudioManager::Instance()
{
    if (sInstance == nullptr)
    {
        sInstance = new AudioManager();
    }
    return sInstance;
}

void AudioManager::Release()
{
    delete sInstance;
    sInstance = nullptr;
}

AudioManager::AudioManager()
{
    mAssetMgr = AssetManager::Instance();

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) < 0)
    {
        printf("Mixer Initialization Error: %s\n", Mix_GetError());
    }
}

AudioManager::~AudioManager()
{
    mAssetMgr = nullptr;
    Mix_Quit();
}

void AudioManager::PlayMusic(std::string filename, int loops)
{
    Mix_PlayMusic(mAssetMgr->getMusic(filename), loops);
}

void AudioManager::PlaySFX(std::string filename, int channel)
{
    Mix_PlayChannel(channel, mAssetMgr->getSFX(filename), 0);
}
