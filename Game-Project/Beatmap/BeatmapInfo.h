#ifndef _BEATMAPINFO_H
#define _BEATMAPINFO_H

struct BeatmapInfo
{
    int BeatmapID;

    int Mode;

    double Length;

    double BPM;

    double AudioLeadIn;

    float StackLeniency = 0.7f;

    double DistanceSpacing = 1.0;

    int BeatDivisor = 4;

    int GridSize;

    int CountDown;
};

#endif // _BEATMAPINFO_H
