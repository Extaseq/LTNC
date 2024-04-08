#include <iostream>
#include <string>

std::string decToBin(int num) {
    std::string result = "";
    while (num > 0) {
        result = char((num & 1) + '0') + result;
        num >>= 1;
    }
    return result;
}

int binToDec(std::string bin) {
    int result = 0;
    int n = bin.length();
    for (int i = 0; i < n; i++) {
        if (bin[i] == '1') 
            result += (1 << (n - 1 - i));
    }
    return result;
}

int main() {
    std::cout << "Lua chon chuyen doi:\n";
    std::cout << "So chan: Chuyen tu thap phan sang nhi phan.\n";
    std::cout << "So le: Chuyen tu nhi phan sang thap phan.\n";
    std::cout << "Lua chon cua ban: ";
    long long choice; std::cin >> choice;
    if (choice & 1) {
        std::cout << "Nhap xau nhi phan: ";
        std::string bin; std::cin >> bin;
        std::cout << binToDec(bin);
    } else {
        std::cout << "Nhap so nguyen: ";
        int num; std::cin >> num;
        std::cout << decToBin(num);
    }
}