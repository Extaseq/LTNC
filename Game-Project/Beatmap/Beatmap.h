#ifndef _BEATMAP_H
#define _BEATMAP_H

#include "Formats/Parsing.h"
#include "BeatmapInfo.h"
#include "BeatmapMetadata.h"
#include "BeatmapDifficulty.h"

#include <vector>

struct Beatmap
{
    Beatmap() = default;

    BeatmapInfo beatmapInfo;

    BeatmapMetadata beatmapMetadata;

    std::vector<BeatmapDifficulty> beatmapDifficulty;
};

#endif // _BEATMAP_H
