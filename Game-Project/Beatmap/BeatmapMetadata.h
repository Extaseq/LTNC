#ifndef _BEATMAPMETADATA_H
#define _BEATMAPMETADATA_H

#include <string>

struct BeatmapMetadata
{
    BeatmapMetadata() = default;

    std::string Title;

    std::string TitleUnicode;

    std::string Artist;

    std::string ArtistUnicode;

    int PreviewTime;

    std::string SampleSet;

    std::string AudioFile;

    std::string BackgroundFile;
};

#endif // _BEATMAPMETADATA_H
