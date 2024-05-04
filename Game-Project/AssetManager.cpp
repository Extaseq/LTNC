#include "AssetManager.h"

AssetManager* AssetManager::sInstance = nullptr;

AssetManager* AssetManager::Instance()
{
    if (sInstance == nullptr)
    {
        sInstance = new AssetManager();
    }
    return sInstance;
}

void AssetManager::Release()
{
    delete sInstance;
    sInstance = nullptr;
}

AssetManager::AssetManager()
{

}

AssetManager::~AssetManager()
{
    for (auto Texture : mTextures)
    {
        if (Texture.second != nullptr)
        {
            SDL_DestroyTexture(Texture.second);
        }
    }
    mTextures.clear();
}

SDL_Texture* AssetManager::GetTexture(const std::string& fileName)
{
    if (mTextures[fileName] == nullptr)
    {
        mTextures[fileName] = Graphics::Instance()->LoadTexture(fileName);
    }
    return mTextures[fileName];
}

Mix_Music* AssetManager::getMusic(const std::string& dir)
{
    if (mMusics.find(dir) == mMusics.end())
    {
        mMusics[dir] = Mix_LoadMUS(dir.c_str());
        if (mMusics[dir] == nullptr)
        {
            printf("Music file: %s. Load error: %s\n", dir.c_str(), Mix_GetError());
        }
    }
    return mMusics[dir];
}

Mix_Chunk* AssetManager::getSFX(const std::string& dir)
{
    if (mSFX.find(dir) == mSFX.end())
    {
        mSFX[dir] = Mix_LoadWAV(dir.c_str());
        if (mSFX[dir] == nullptr)
        {
            printf("SFX file: %s. Load error: %s\n", dir.c_str(), Mix_GetError());
        }
    }
    return mSFX[dir];
}
