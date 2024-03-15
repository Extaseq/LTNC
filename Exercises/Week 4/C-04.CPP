#include <iostream>
#include <vector>

const int dx[3] = {-1, 0, 1};
const int dy[3] = {-1, 0, 1};

int dfs(std::vector<std::vector<char>>& source, int row, int col) {
	int cnt = 0, rowDx = 0, colDy = 0;
	for (int i = 0; i < 3; i++) {
		rowDx = row + dx[i];
		if (rowDx < 0 || rowDx >= source.size())
			continue;
		for (int j = 0; j < source[row].size(); j++) {
			colDy = col + dy[j];
			if (colDy < 0 || colDy >= source[row].size())
				continue;
			cnt += (source[rowDx][colDy] == '*');
		}
	}
	return cnt;
}

int main() {
	int n, m; std::cin >> n >> m;
	std::vector<std::vector<char>> source;
	source.resize(n, std::vector<char>(m));
	for (auto &row : source)
		for (auto &col : row) 
			std::cin >> col;
	
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (source[i][j] == '*')
				std::cout << "* ";
			else std::cout << char(dfs(source, i, j) + '0') << " ";
		}
		std::cout << "\n";
	}
}