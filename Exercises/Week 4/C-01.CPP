#include <iostream>
#include <unordered_map>

int main() {
	std::unordered_map<int, int> lib;
	int n, temp; std::cin >> n;
	for (int i = 0; i < n; i++) {
		std::cin >> temp;
		if (lib.find(temp) != lib.end()) {
			std::cout << "Yes";
			return 0;
		}
		lib[temp]++;
	}
	std::cout << "No";
}