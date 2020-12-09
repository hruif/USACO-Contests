#include <iostream>
#include <fstream>
#include <string.h>

#define ll long long

using namespace std;

int R, C;
char grid[15][15];
ll found[15][15];

ll findPaths(int x, int y) {
	if (x == R - 1 && y == C - 1) return 1;
	if (found[x][y] != -1) return found[x][y];

	ll total = 0;

	for (int i = x + 1; i < R; i++) {
		for (int j = y + 1; j < C; j++) {
			if (grid[i][j] != grid[x][y]) total += findPaths(i, j);
		}
	}

	found[x][y] = total;
	return total;
}

int main() {
	ifstream fin("hopscotch.in");
	ofstream fout("hopscotch.out");

	fin >> R >> C;
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			fin >> grid[i][j];
		}
	}
	memset(found, -1, sizeof(found));

	ll total = findPaths(0, 0);

	fout << total << '\n';
}