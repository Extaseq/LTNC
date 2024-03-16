#include <iostream>
#include <vector>
#include <math.h>

int main() {
    int n; std::cin >> n;

    std::vector<double> nums(n);
    for (auto &num : nums)
        std::cin >> num;

    double mean = 0;
    for (auto num : nums)
        mean += num;
    mean = mean / n;

    double variance = 0;
    for (auto num : nums)
        variance += pow(num - mean, 2);
    variance = variance / n;

    std::cout << mean << " " << variance;
    return 0;
}
