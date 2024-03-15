#include <iostream>
#include <vector>
#include <string>
#include <math.h>

std::vector<std::string> ones = {"", "One ", "Two ", "Three ", "Four ", "Five ",
                                 "Six ", "Seven ", "Eight ", "Nine ", "Ten ",
                                 "Eleven ", "Twelve ", "Thirteen ", "Fourteen ",
                                 "Fifteen ", "Sixteen ", "Seventeen ", "Eighteen ", "Nineteen "};

std::vector<std::string> tens = {"", "Ten ", "Twenty ", "Thirty ", "Forty ", "Fifty ", "Sixty ",
                                 "Seventy ", "Eighty ", "Ninety "};

std::vector<std::string> suffix = {"", "Thousand ", "Million "};

std::string rec(int n) {
    if (n < 20)
        return ones[n];
    if (n < 100)
        return tens[n / 10] + ones[n % 10];
    if (n < 1000)
        return ones[n / 100] + "Hundred " + rec(n % 100);

    for (int i = 2; i >= 0; --i) {
        int base = (int)std::pow(1000, i);
        if (n > base)
            return rec(n / base) + suffix[i] + rec(n % base);
    }

    return "";
}

std::string numberToWords(int num) {
    if (num == 0)
        return "Zero";

    return rec(num);
}

int main() {
    int n; std::cin >> n;

    std::cout << numberToWords(n);
}
