#include <iostream>

int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

int main() {
    int a, b; std::cin >> a >> b;
    if (gcd(a, b) == 1) 
        std::cout << "YES";
    else std::cout << "NO";
}