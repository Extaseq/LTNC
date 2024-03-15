#include <iostream>

void GenerateSpiralMatrix(int width, int height) {
    int matrix[height][width], number = 1;
    int rowStart = 0, rowEnd = height - 1;
    int colStart = 0, colEnd = width - 1;

    while (rowStart <= height && colStart <= width) {
        for (int i = colStart; i <= colEnd; i++) 
            matrix[rowStart][i] = number++;
        rowStart++;

        for (int i = rowStart; i <=rowEnd; i++) 
            matrix[i][colEnd] = number++;
        colEnd--;

        for (int i = colEnd; i >= colStart; i--)
            matrix[rowEnd][i] = number++;
        rowEnd--;

        for (int i = rowEnd; i >= rowStart; i--)
            matrix[i][colStart] = number++;\
        colStart++;
    }

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++)
            std::cout << matrix[i][j] << " ";
        std::cout << "\n";
    }
}

int main() {
    int width, height; std::cin >> width >> height;
    GenerateSpiralMatrix(width, height);
}