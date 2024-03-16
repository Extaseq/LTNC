#include <iostream>
#include <vector>

void Generate(int numRows) {
    std::vector<std::vector<int>> pascal;
    pascal.resize(numRows, std::vector<int>());
    for (int i = 0; i < numRows; i++) {
        pascal[i].resize(i + 1);
        pascal[i][0] = pascal[i][i] = 1;
        for (int j = 1; j < i; j++)
            pascal[i][j] = pascal[i - 1][j - 1]
                         + pascal[i - 1][j];
    }

    for (auto row : pascal) {
        for (auto col : row) 
            std::cout << col << " ";
        std::cout << "\n";
    }
}

int main() {
    int n; std::cin >> n;
    Generate(n);
}