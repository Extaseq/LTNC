#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <dirent.h>
#include <unordered_map>
#include <algorithm>
#include "Parsing.h"
#include "../Beatmap.h"

#define HashableFileType ".osu"
#define Key first
#define Value second

class Decoder {
public:
    Decoder() = default;

    static void getDecoder(const std::string& beatmapName, Beatmap& beatmap)
    {
        std::string directory = "Songs/" + beatmapName;

        beatmap.beatmapMetadata.AudioFileDir = directory + "/";

        std::string fileName;

        DIR *dir;

        struct dirent *entry;

        if ((dir = opendir(directory.c_str())) != NULL)
        {
            while ((entry = readdir(dir)) != NULL)
            {
                fileName = entry->d_name;

                if (fileName != "." && fileName != ".." && getFileExtension(fileName) == HashableFileType)
                {
                    readDifficultFile(directory + "/" + fileName, beatmap);
                }

                if (getFileExtension(fileName) == ".jpg" or getFileExtension(fileName) == ".png")
                {
                    beatmap.beatmapMetadata.BackgroundFile = directory + "/" + fileName;
                }
            }
        }

        std::string audiofile = beatmap.beatmapMetadata.AudioFilename;
        if (audiofile[0] == ' ') audiofile = audiofile.substr(1);


        beatmap.beatmapMetadata.AudioFileDir += audiofile;
    }

    static void readDifficultFile(const std::string &fileName, Beatmap &beatmap)
    {
        std::unordered_map<std::string, int> SectionType = {
            {"[General]", 1}, {"[Editor]", 2}, {"[Metadata]", 3},
            {"[Difficulty]", 4}, {"[Events]", 5}, {"[TimingPoints]", 6},
            {"[Colours]", 7}, {"[HitObjects]", 8}
        };

        std::vector<std::vector<std::string>> fileContent;
        fileContent.resize(9, std::vector<std::string>());

        std::ifstream inputFile(fileName);
        if (!inputFile.is_open())
        {
            std::cerr << "Can't open file.\n";
            return;
        }

        TypeName Section;

        std::string line; int index = Section.NaN;
        while (std::getline(inputFile, line))
        {
            auto find = SectionType.find(line);
            if (find != SectionType.end()) index = find->second;
            fileContent[index].push_back(line);
        }

        for (size_t index = 1; index < fileContent.size(); ++index)
        {
            if (fileContent[index].empty()) continue;

            trimVector(fileContent[index]);
        }

        handleGeneral(fileContent[Section.General], beatmap);

        handleEditor(fileContent[Section.Editor], beatmap);

        handleMetadata(fileContent[Section.Metadata], beatmap);

        handleDifficulty(fileContent[Section.Difficulty], beatmap);

        /* No need */
        // handleEvents(fileContent[Section.Events], beatmap);

        handleTimingPoints(fileContent[Section.TimingPoints], beatmap);

        handleHitObjects(fileContent[Section.HitObjects], beatmap);
    }

    static void handleGeneral(const std::vector<std::string>& sectionInfo, Beatmap& beatmap)
    {
        std::pair<std::string, std::string> pair;

        size_t length = sectionInfo.size();

        for (size_t line = 1; line < length; ++line)
        {
            pair = keyValuePair(sectionInfo[line]);

            if (pair.Key == "AudioFilename")
            {
                beatmap.beatmapMetadata.AudioFilename = pair.second;
            }

            if (pair.Key == "AudioLeadIn")
            {
                beatmap.beatmapInfo.AudioLeadIn = Parsing::ParseInt(pair.Value);
            }

            if (pair.Key == "PreviewTime")
            {
                int Time = Parsing::ParseInt(pair.Value);
                beatmap.beatmapMetadata.PreviewTime = (Time == -1) ? 0 : Time;
            }

            if (pair.Key == "Countdown")
            {
                beatmap.beatmapInfo.CountDown = Parsing::ParseInt(pair.Value);
            }

            if (pair.Key == "SampleSet")
            {
                beatmap.beatmapMetadata.SampleSet = pair.Value;
            }

            if (pair.Key == "StackLeniency")
            {
                beatmap.beatmapInfo.StackLeniency = Parsing::ParseFloat(pair.Value);
            }

            if (pair.Key == "Mode")
            {
                beatmap.beatmapInfo.Mode = Parsing::ParseInt(pair.Value);
            }
        }
    }

    static void handleEditor(const std::vector<std::string>& sectionInfo, Beatmap& beatmap)
    {
        std::pair<std::string, std::string> pair;

        size_t length = sectionInfo.size();

        for (size_t index = 1; index < length; ++index)
        {
            pair = keyValuePair(sectionInfo[index]);

            if (pair.Key == "DistanceSpacing")
            {
                beatmap.beatmapInfo.DistanceSpacing = std::max(0.0, Parsing::ParseDouble(pair.Value));
            }

            if (pair.Key == "BeatDivisor")
            {
                beatmap.beatmapInfo.BeatDivisor = Parsing::ParseInt(pair.Value);
            }

            if (pair.Key == "GridSize")
            {
                beatmap.beatmapInfo.GridSize = Parsing::ParseInt(pair.Value);
            }
        }
    }

    static void handleMetadata(const std::vector<std::string>& sectionInfo, Beatmap& beatmap)
    {
        std::pair<std::string, std::string> pair;

        size_t length = sectionInfo.size();

        for (size_t index = 1; index < length; ++index)
        {
            pair = keyValuePair(sectionInfo[index]);

            if (pair.Key == "Title")
            {
                beatmap.beatmapMetadata.Title = pair.Value;
            }

            if (pair.Key == "TitleUnicode")
            {
                beatmap.beatmapMetadata.TitleUnicode = pair.Value;
            }

            if (pair.Key == "Artist")
            {
                beatmap.beatmapMetadata.Artist = pair.Value;
            }

            if (pair.Key == "ArtistUnicode")
            {
                beatmap.beatmapMetadata.ArtistUnicode = pair.Value;
            }

            if (pair.Key == "Version")
            {
                beatmap.beatmapDifficulty.push_back(BeatmapDifficulty(pair.Value));
            }

            if (pair.Key == "BeatmapSetID")
            {
                beatmap.beatmapInfo.BeatmapID = Parsing::ParseInt(pair.Value);
            }
        }
    }

    static void handleDifficulty(const std::vector<std::string>& sectionInfo, Beatmap& beatmap)
    {
        std::pair<std::string, std::string> pair;

        size_t length = sectionInfo.size();

        for (size_t index = 1; index < length; ++index)
        {
            pair = keyValuePair(sectionInfo[index]);

            if (pair.Key == "HPDrainRate")
            {
                beatmap.beatmapDifficulty.back().DrainRate = Parsing::ParseFloat(pair.Value);
            }

            if (pair.Key == "CircleSize")
            {
                beatmap.beatmapDifficulty.back().CircleSize = Parsing::ParseFloat(pair.Value);
            }

            if (pair.Key == "OverallDifficulty")
            {
                beatmap.beatmapDifficulty.back().OverallDifficulty = Parsing::ParseFloat(pair.Value);
            }

            if (pair.Key == "ApproachRate")
            {
                beatmap.beatmapDifficulty.back().ApproachRate = Parsing::ParseFloat(pair.Value);
            }

            if (pair.Key == "SliderMultiplier")
            {
                beatmap.beatmapDifficulty.back().SliderMultiplier = Parsing::ParseFloat(pair.Value);
            }

            if (pair.Key == "SliderTickRate")
            {
                beatmap.beatmapDifficulty.back().SliderTickRate = Parsing::ParseFloat(pair.Value);
            }
        }
    }

    static void handleEvents(const std::vector<std::string>& sectionInfo, Beatmap& beatmap)
    {
        return;
    }

    /*
    Timing point syntax: time,beatLength,meter,sampleSet,sampleIndex,volume,uninherited,effects
    {
        int time:          Start time of the timing section, in milliseconds from the beginning
                           of the beatmap's audio. The end of the timing section is the next
                           timing point's time (or never, if this is the last timing point).

        double beatLength: This property has two meanings:
                           - For uninherited timing points, the duration of a beat, in milliseconds.
                           - For inherited timing points, a negative inverse slider velocity
                           multiplier, as a percentage.

        int meter:         Amount of beats in a measure. Inherited timing points ignore this property.

        int sampleSet:     Default sample set for hit objects (0 = beatmap default, 1 = normal,
                           2 = soft, 3 = drum).

        int sampleIndex:   Custom sample index for hit objects.

        int volume:        Volume percentage for hit objects.

        bool uninherited:  Whether or not the timing point is uninherited.

        int effects:       Bit flags that give the timing point extra effects.
    }
    */
    static void handleTimingPoints(const std::vector<std::string>& sectionInfo, Beatmap& beatmap)
    {
        std::vector<std::string> timingsPoints;

        size_t length = sectionInfo.size();

        BeatmapDifficulty &BeatmapDifficulty = beatmap.beatmapDifficulty.back();

        for (size_t index = 1; index < length; ++index)
        {
            timingsPoints = split(sectionInfo[index]);

            int time = Parsing::ParseInt(timingsPoints[0]);

            double beatLength = Parsing::ParseDouble(timingsPoints[1]);

            if (beatLength > 0)
            {
                beatmap.beatmapInfo.BPM = 1.0 / beatLength * 1000.0 * 60.0;
            }

            int meter = Parsing::ParseInt(timingsPoints[2]);

            int sampleSet = Parsing::ParseInt(timingsPoints[3]);

            int sampleIndex = Parsing::ParseInt(timingsPoints[4]);

            int volume = Parsing::ParseInt(timingsPoints[5]);

            bool uninherited = Parsing::ParseInt(timingsPoints[6]);

            int effect = Parsing::ParseInt(timingsPoints[7]);

            BeatmapDifficulty.timingPoints.push_back(
                TimingPoint(time, beatLength, meter, sampleSet, sampleIndex, volume, uninherited, effect)
            );
        }
    }

    /*
    Hit object syntax: x,y,time,type,hitSound,objectParams,hitSample
    {
        int x, y:          Position of the object.

        int time:          Time when the object is to be hit, in milliseconds
                           from the beginning of the beatmap's audio.

        int type:          Bit flags indicating the type of the object.

        int hitSound:      Bit flags indicating the hitsound applied to the object.

        List objectParams: Extra parameters specific to the object's type.

        List hitSample:    Information about which samples are played when the object is hit. It is closely related to hitSound; see the hitsounds section. If it is not written, it defaults to 0:0:0:0:.
    }*/

    static void handleHitObjects(const std::vector<std::string>& sectionInfo, Beatmap& beatmap)
    {
        std::vector<std::string> hitObject;

        size_t length = sectionInfo.size();

        for (size_t index = 1; index < length; ++index)
        {
            hitObject = split(sectionInfo[index]);

            int x = Parsing::ParseInt(hitObject[0]);

            int y = Parsing::ParseInt(hitObject[1]);

            int time = Parsing::ParseInt(hitObject[2]);

            int type = Parsing::ParseInt(hitObject[3]);

            int hitSound = Parsing::ParseInt(hitObject[4]);

            std::vector<std::string> hitSample = split(hitObject[5], ':');

            beatmap.beatmapDifficulty.back().hitObjects.push_back(HitObject(x, y, time, type, hitSound, hitSample));
        }
    }

    static std::pair<std::string, std::string> keyValuePair(std::string line, char seperator = ':')
    {
        size_t pos = line.find(seperator);

        return std::make_pair(line.substr(0, pos), line.substr(pos + 1));
    }

    static std::vector<std::string> split(std::string line, char seperator = ',')
    {
        std::vector<std::string> splited;

        std::istringstream iss(line);

        std::string token;

        while (std::getline(iss, token, seperator))
        {
            splited.push_back(token);
        }

        return splited;
    }

    static std::string getFileExtension(const std::string& dir)
    {
        if (dir.size() < 5) return "";

        return dir.substr(dir.size() - 4);
    }

    template <class T> static void trimVector(std::vector<T>& vec)
    {
        if (!vec.empty())
        {
            while (vec.back().size() == 0) vec.pop_back();
        }
    }

private:
    struct TypeName
    {
        int NaN = 0;
        int General = 1;
        int Editor = 2;
        int Metadata = 3;
        int Difficulty = 4;
        int Events = 5;
        int TimingPoints = 6;
        int Colours = 7;
        int HitObjects = 8;
    };
};
