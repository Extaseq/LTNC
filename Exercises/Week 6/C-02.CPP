#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <queue>

class MineSweep {
public:
    MineSweep(int n, int m, int k) : height(n), width(m), mines(k) {
        used = 0, maxTurns = width * height - mines;
        board.resize(height, std::vector<char>(width, 'E'));
        unRevealed.resize(height, std::vector<char>(width, 'E'));
    }

    void generateMine() {
        std::srand(static_cast<int>(std::time(nullptr)));

        int x, y;
        for (int i = 0; i < mines; i++) {
            x = std::rand() % height;
            y = std::rand() % width;
            board[x][y] = 'X';
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
            if (!inBoard(xMove, yMove)) {
                std::cout << "Invalid input.\n";
            } else return;
        }
    }

    bool inBoard(int x, int y) {
        return (x >= 0 && x < height) && (y >= 0 && y < width);
    }

    void bfs(int x, int y) {
        std::queue<std::pair<int, int>> q;
        q.push({x, y});

        while (!q.empty()) {
            auto cur = q.front(); q.pop();
            int x = cur.first;
            int y = cur.second;

            int cnt = 0;
            for (auto m : move) {
                int dx = x + m[0];
                int dy = y + m[1];
                if (inBoard(dx, dy) && board[dx][dy] == 'X')
                    cnt++;
            }

            if (cnt > 0) 
                unRevealed[x][y] = board[x][y] = static_cast<char>(cnt + '0');
            else {
                unRevealed[x][y] = board[x][y] = '0';
                for (auto m : move) {
                    int dx = x + m[0];
                    int dy = y + m[1];
                    if (inBoard(dx, dy) && board[dx][dy] == 'E') {
                        q.push({dx, dy});
                        unRevealed[dx][dy] = board[dx][dy] = '0';
                    }
                }
            }
        }
    }

    void updateBoard(int x, int y) {
        if (board[x][y] == 'X') {
            unRevealed[x][y] = 'X';
            return;
        }

        bfs(x, y);
    }

    void update() {
        int x = -1, y = -1;
        getInput(x, y);
        updateBoard(x, y);

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