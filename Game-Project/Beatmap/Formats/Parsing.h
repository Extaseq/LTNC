#pragma once

#include <stdexcept>
#include <string>
#include <limits>
#include <sstream>
#include <cmath>

class Parsing
{
public:

    static constexpr int MAX_COORDINATES_VALUE = 131072;

    static constexpr double MAX_PARSE_VALUE = std::numeric_limits<int>::max();

    static float ParseFloat(const std::string& input, float parseLimit = MAX_PARSE_VALUE, bool allowNaN = false)
    {
        float output = std::stof(input);

        if (output < -parseLimit) throw std::overflow_error("Value is too low");
        if (output > parseLimit) throw std::overflow_error("Value is too high");

        if (!allowNaN && std::isnan(output)) throw std::invalid_argument("Not a number");

        return output;
    }

    static double ParseDouble(const std::string& input, double parseLimit = MAX_PARSE_VALUE, bool allowNaN = false)
    {
        double output = std::stod(input);

        if (output < -parseLimit) throw std::overflow_error("Value is too low");
        if (output > parseLimit) throw std::overflow_error("Value is too high");

        if (!allowNaN && std::isnan(output)) throw std::invalid_argument("Not a number");

        return output;
    }

    static int ParseInt(const std::string& input, int parseLimit = MAX_PARSE_VALUE)
    {
        int output = std::stoi(input);

        if (output < -parseLimit) throw std::overflow_error("Value is too low");
        if (output > parseLimit) throw std::overflow_error("Value is too high");

        return output;
    }
};
