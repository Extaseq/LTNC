#ifndef _ASSETMANAGER_H
#define _ASSETMANAGER_H

#include "Graphics.h"

#include <unordered_map>

class AssetManager
{
private:

    static AssetManager* sInstance;

    std::unordered_map<std::string, SDL_Texture*> mTextures;

public:

    static AssetManager* Instance();

    static void Release();

    SDL_Texture* GetTexture(const std::string& fileName);

private:

    AssetManager();

    ~AssetManager();
};

#endif // _ASSETMANAGER_H
