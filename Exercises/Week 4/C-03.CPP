#include <iostream>
#include <string>

std::string to_string(int n) {
    std::string result = "";
    while (n > 0) {
        result = char(n % 10 + '0') + result;
        n /= 10;
    }
    return result;
}

bool isIsomorphic(std::string s) {
    int l = 0, r = s.size() - 1;
    while (l < r) {
        if (s[l++] != s[r--])
            return false;
    }
    return true;
}

int main() {
    int T; std::cin >> T;
    while (T--) {
        int l, r, cnt = 0; std::cin >> l >> r;
        for (int i = l; i <= r; i++) 
			cnt += isIsomorphic(to_string(i));
        std::cout << cnt << "\n";
    }
}