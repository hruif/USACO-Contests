/*
ID: ruifanl1
TASK: grazing
LANG: C++
*/

#include <iostream>
#include <fstream>

using namespace std;

int K;
bool barren[5][5];

bool allBarren(int x, int y) {
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			if (!barren[i][j] && (i != x || j != y)) {
				return false;
			}
		}
	}
	return true;
}

int moveCow(int bx, int by, int mx, int my, bool b) {
	if (bx == mx && by == my) {
		if (allBarren(bx, by)) {
			return 1;
		}
		else {
			return 0;
		}
	}
	int combos = 0;
	if (b) {
		barren[bx][by] = true;
		if (bx > 0) {
			if (!barren[bx - 1][by]) {
				combos += moveCow(bx - 1, by, mx, my, false);
			}
		}
		if (bx < 4) {
			if (!barren[bx + 1][by]) {
				combos += moveCow(bx + 1, by, mx, my, false);
			}
		}
		if (by > 0) {
			if (!barren[bx][by - 1]) {
				combos += moveCow(bx, by - 1, mx, my, false);
			}
		}
		if (by < 4) {
			if (!barren[bx][by + 1]) {
				combos += moveCow(bx, by + 1, mx, my, false);
			}
		}
		barren[bx][by] = false;
	}
	else {
		barren[mx][my] = true;
		if (mx > 0) {
			if (!barren[mx - 1][my]) {
				combos += moveCow(bx, by, mx - 1, my, true);
			}
		}
		if (mx < 4) {
			if (!barren[mx + 1][my]) {
				combos += moveCow(bx, by, mx + 1, my, true);
			}
		}
		if (my > 0) {
			if (!barren[mx][my - 1]) {
				combos += moveCow(bx, by, mx, my - 1, true);
			}
		}
		if (my < 4) {
			if (!barren[mx][my + 1]) {
				combos += moveCow(bx, by, mx, my + 1, true);
			}
		}
		barren[mx][my] = false;
	}

	return combos;
}

int main() {
	ifstream fin("grazing.in");
	fin >> K;
	for (int i = 0; i < K; i++) {
		int x, y;
		fin >> x >> y;
		barren[x - 1][y - 1] = true;
	}
	int ans = moveCow(0, 0, 4, 4, true);
	ofstream fout("grazing.out");
	fout << ans << '\n';
}