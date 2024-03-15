#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    int n, temp; std::cin >> n;

    std::vector<int> times(n);
    for (auto &t : times) std::cin >> t;
    std::sort(times.begin(), times.end());

    int totalTime = 0, currentTime = 0;
    for (int i = 0; i < n; i++) {
        totalTime += currentTime;
        currentTime += times[i];
    }
    std::cout << totalTime;
}