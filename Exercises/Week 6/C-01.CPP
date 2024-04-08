#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <windows.h>

class MineSweep {
public:
    MineSweep(int n, int m, int k) : height(n), width(m), mines(k) {
        used = 0, maxTurns = width * height - mines;
        board.resize(height, std::vector<char>(width, '0'));
        unRevealed.resize(height, std::vector<char>(width, 'O'));
    }

    void generateMine() {
        std::srand(static_cast<int>(std::time(nullptr)));

        int x, y;
        for (int i = 0; i < mines; i++) {
            x = std::rand() % height;
            y = std::rand() % width;
            addNumber(x, y);
        }
    }

    void addNumber(int x, int y) {
        board[x][y] = 'X';
        int dx, dy;
        for (auto m : move) {
            dx = x + m[0];
            dy = y + m[1];
            if (!validInput(dx, dy))
                continue;

            if (board[dx][dy] != 'X')
                board[dx][dy] = static_cast<char>(board[dx][dy] + 1);
        }
    }

    void printBoard() const {
        system("cls");
        for (int i = 0; i < height; i++) {
            for (int j  = 0; j < width; j++)
                std::cout << unRevealed[i][j] << " ";
            std::cout << "\n";
        }
    }

    void getInput(int &xMove, int &yMove) {
        while (true) {
            std::cin >> xMove >> yMove;
            if (!validInput(xMove, yMove)) {
                std::cout << "Invalid input.\n";
            } else return;
        }
    }

    bool validInput(int x, int y) {
        return (x >= 0 && x < height) && (y >= 0 && y < width);
    }

    void update() {
        int x = -1, y = -1;
        getInput(x, y);
        unRevealed[x][y] = board[x][y];

        std::cout << used << " " << maxTurns << "\n";

        if (board[x][y] == 'X') {
            gameOver = true;
            return;
        } 

        used++;
        if (used == maxTurns) {
            gameOver = true;
        }
    }

    void over() {
        std::cout << "YOU'RE DEAD!\n";
    }

    bool win() {
        return used == maxTurns;
    }

    bool isRunning() const {
        return !gameOver;
    }

private:
    int width, height, mines, used, maxTurns;
    std::vector<std::vector<char>> board, unRevealed;
    std::vector<std::vector<int>> move = {
        {-1, -1}, {0, -1}, {1, -1},
        {-1, 0}          , {1, 0},
        {-1, 1},  {0, 1} , {1, 1}
    };

    bool gameOver = false;
};

int main() {
    int n, m, k; std::cin >> n >> m >> k;
    MineSweep Game(n, m, k);
    Game.printBoard();
    Game.generateMine();
    while (Game.isRunning()) {
        Game.update();
        Game.printBoard();
    }
    if (Game.win()) {
        std::cout << "Game won!\n";
    } else Game.over();
}
