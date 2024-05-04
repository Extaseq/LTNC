#pragma once

#include <iostream>
#include <string>
#include <vector>

struct TimingPoint
{
    TimingPoint() = default;

    TimingPoint(int time_, double beatLength_, int meter_, int sampleSet_, int sampleIndex_, int volume_, bool uninherited_, int effects_)
        : time(time_), beatLength(beatLength_), meter(meter_), sampleSet(sampleSet_), sampleIndex(sampleIndex_), volume(volume_), uninherited(uninherited_), effects(effects_)
    {
    }

    int time;

    double beatLength;

    int meter;

    int sampleSet;

    int sampleIndex;

    int volume;

    bool uninherited;

    int effects;

    void printTimingPoint()
    {
        std::cout << time << "," << beatLength << "," << meter << "," << sampleSet << "," << sampleIndex << "," << volume << "," << (uninherited ? "true" : "false") << "," << effects << "\n";
    }
};

struct HitObject
{
    class TypeBitFlags
    {
        int HitCircle = 0;

        int Slider = 1;

        int NewCombo = 2;

        int Spinner = 3;

        /*
            4, 5, 6 is not relevant
        */

       int Hold = 7;
    };

    class HitSoundBitFlags
    {
        int Normal = 0;

        int Whistle = 1;

        int Finish = 2;

        int Clap = 3;
    };

    struct HitSample
    {
        int normalSet = 0;

        int additionalSet = 0;

        int index = 0;

        int volume = 0;

        int holdEnd;

        std::string filename = "";

        HitSample(std::vector<std::string> hitSample)
        {
            if (hitSample.size() == 4)
            {
                normalSet = Parsing::ParseInt(hitSample[0]);

                additionalSet = Parsing::ParseInt(hitSample[1]);

                index = Parsing::ParseInt(hitSample[2]);

                volume = Parsing::ParseInt(hitSample[3]);
            }

            if (hitSample.size() == 5)
            {
                if (isalpha(hitSample[4][1]))
                {
                    normalSet = Parsing::ParseInt(hitSample[0]);

                    additionalSet = Parsing::ParseInt(hitSample[1]);

                    index = Parsing::ParseInt(hitSample[2]);

                    volume = Parsing::ParseInt(hitSample[3]);

                    filename = hitSample[4];
                }
                    else
                {
                    holdEnd = Parsing::ParseInt(hitSample[0]);

                    normalSet = Parsing::ParseInt(hitSample[1]);

                    additionalSet = Parsing::ParseInt(hitSample[2]);

                    index = Parsing::ParseInt(hitSample[3]);

                    volume = Parsing::ParseInt(hitSample[4]);
                }
            }

            if (hitSample.size() == 6)
            {
                holdEnd = Parsing::ParseInt(hitSample[0]);

                normalSet = Parsing::ParseInt(hitSample[1]);

                additionalSet = Parsing::ParseInt(hitSample[2]);

                index = Parsing::ParseInt(hitSample[3]);

                volume = Parsing::ParseInt(hitSample[4]);

                filename = hitSample[5];
            }
        }
    };

    int x;

    int y;

    int time;

    int type;

    int hitSound;

    HitSample* hitSample = nullptr;

    HitObject(int x_, int y_, int time_, int type_, int hitSound_, std::vector<std::string> hitSample_)
        : x(x_), y(y_), time(time_), type(type_), hitSound(hitSound_)
    {
        /*No need*/
        // this->hitSample = new HitSample(hitSample_);
    }
};

struct BeatmapDifficulty
{
    std::string difficultName;

    float DrainRate;

    float CircleSize;

    float OverallDifficulty;

    float ApproachRate;

    float SliderMultiplier;

    float SliderTickRate;

    std::vector<TimingPoint> timingPoints;

    std::vector<HitObject> hitObjects;

    BeatmapDifficulty() = default;

    BeatmapDifficulty(const std::string& difficultName_) : difficultName(difficultName_)
    {
    }

    void printBeatmapDifficulty()
    {
        std::cout << "Difficulty Name: " << difficultName << std::endl;
        std::cout << "Drain Rate: " << DrainRate << std::endl;
        std::cout << "Circle Size: " << CircleSize << std::endl;
        std::cout << "Overall Difficulty: " << OverallDifficulty << std::endl;
        std::cout << "Approach Rate: " << ApproachRate << std::endl;
        std::cout << "Slider Multiplier: " << SliderMultiplier << std::endl;
        std::cout << "Slider Tick Rate: " << SliderTickRate << std::endl;
    }
};



