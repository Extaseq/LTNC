#include <iostream>
#include <vector>

void generateMagicSquare(int n) {
    std::vector<std::vector<int>> magicSquare;
    magicSquare.resize(n, std::vector<int>(n, 0));

    int row = 0;
    int col = n / 2;
    int num = 1;

    while (num <= n * n) {
        magicSquare[row][col] = num;

        int nextRow = (row - 1 + n) % n;
        int nextCol = (col + 1) % n;

        if (magicSquare[nextRow][nextCol] != 0) {
            row = (row + 1) % n;
        } else {
            row = nextRow;
            col = nextCol;
        }
        num++;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) 
            std::cout << magicSquare[i][j] << " ";
        std::cout << "\n";
    }
}


int main() {
	int n; std::cin >> n;
	generateMagicSquare(n);
}