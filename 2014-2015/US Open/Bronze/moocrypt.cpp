#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

int R, C;
char grid[50][50];

int findmoos(char M, char O) {
	if (M == 'M' || O == 'O') return 0;

	int total = 0;

	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			if (grid[i][j] != O) continue;

			bool hor = j > 0 && j < C - 1;
			bool vert = i > 0 && i < R - 1;

			if (hor) {
				if (grid[i][j - 1] == M && grid[i][j + 1] == O) total++;
				if (grid[i][j - 1] == O && grid[i][j + 1] == M) total++;
			}
			if (vert) {
				if (grid[i - 1][j] == M && grid[i + 1][j] == O) total++;
				if (grid[i - 1][j] == O && grid[i + 1][j] == M) total++;
			}
			if (hor && vert) {
				if (grid[i - 1][j - 1] == M && grid[i + 1][j + 1] == O) total++;
				if (grid[i - 1][j - 1] == O && grid[i + 1][j + 1] == M) total++;

				if (grid[i - 1][j + 1] == M && grid[i + 1][j - 1] == O) total++;
				if (grid[i - 1][j + 1] == O && grid[i + 1][j - 1] == M) total++;
			}
		}
	}

	return total;
}

int main() {
	ifstream fin("moocrypt.in");
	ofstream fout("moocrypt.out");

	fin >> R >> C;
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			fin >> grid[i][j];
		}
	}

	int maxmoos = 0;
	for (int i = 0; i < 26; i++) {
		for (int j = 0; j < 26; j++) {
			if (i == j) continue;

			maxmoos = max(maxmoos, findmoos(i + 'A', j + 'A'));
		}
	}

	fout << maxmoos << '\n';
}