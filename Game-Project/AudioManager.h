#ifndef _AUDIOMANAGER_H
#define _AUDIOMANAGER_H

#include "AssetManager.h"

class AudioManager
{
private:

    static AudioManager* sInstance;

    AssetManager* mAssetMgr;

public:

    static AudioManager* Instance();

    static void Release();

    void PlayMusic(std::string filename, int loops = -1);

    void PlaySFX(std::string filename, int channel = 0);

private:

    AudioManager();

    ~AudioManager();
};

#endif // _AUDIOMANAGER_H
