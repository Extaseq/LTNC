#ifndef _ASSETMANAGER_H
#define _ASSETMANAGER_H

#include "Graphics.h"

#include <unordered_map>
#include <SDL_mixer.h>
#include <SDL_image.h>
#include <SDL.h>

class AssetManager
{
private:

    static AssetManager* sInstance;

    std::unordered_map<std::string, SDL_Texture*> mTextures;

    std::unordered_map<std::string, Mix_Music*> mMusics;

    std::unordered_map<std::string, Mix_Chunk*> mSFX;

public:

    static AssetManager* Instance();

    static void Release();

    SDL_Texture* GetTexture(const std::string& fileName);

    Mix_Music* GetMusic(const std::string& dir);

    Mix_Chunk* GetSFX(const std::string& dir);

private:

    AssetManager();

    ~AssetManager();
};

#endif // _ASSETMANAGER_H
