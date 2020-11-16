#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

int B, E;
char dirs[2][50001];
int moves[2][50001];

int main() {
	ifstream fin("input.in");
	fin >> B >> E;
	for (int i = 0; i < B; i++) {
		fin >> moves[0][i] >> dirs[0][i];
	}
	for (int i = 0; i < E; i++) {
		fin >> moves[1][i] >> dirs[1][i];
	}
	int BPos = 0, EPos = 0;
	int BM = 0, EM = 0;
	int moos = 0;
	bool apart = false;
	while (BM != max(B, E) && EM != max(B, E)) {
		if (dirs[0][BM] == 'L') {
			moves[0][BM]--;
			BPos--;
		}
		else if (dirs[0][BM] == 'R') {
			moves[0][BM]--;
			BPos++;
		}
		if (dirs[1][EM] == 'L') {
			moves[1][EM]--;
			EPos--;
		}
		else if (dirs[1][EM] == 'R') {
			moves[1][EM]--;
			EPos++;
		}
		if (BPos != EPos) {
			apart = true;
		}
		else {
			if (apart) {
				moos++;
			}
			apart = false;
		}

		if (moves[0][BM] == 0 && dirs[0][BM]) {
			BM++;
		}
		if (moves[1][EM] == 0 && dirs[1][EM]) {
			EM++;
		}
	}
	cout << moos;
}