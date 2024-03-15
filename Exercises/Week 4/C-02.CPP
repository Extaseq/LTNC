#include <iostream>
#include <string>

int main() {
	std::string s; std::cin >> s;
	int l = 0, r = s.size() - 1;
	while (l < r)  {
		if (s[l++] != s[r--]) {
			std::cout << "No";
			return 0;
		}
	}
	std::cout << "Yes";
}