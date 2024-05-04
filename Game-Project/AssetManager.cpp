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
