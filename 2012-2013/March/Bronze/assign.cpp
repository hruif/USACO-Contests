#include <iostream>
#include <fstream>

using namespace std;

int N, K;
bool same[15][15];
bool dif[15][15];
int breed[15];

int findCount(int c) {
	if (c == N) {
		return 1;
	}
	int count = 0;
	for (int i = 0; i < 3; i++) {
		bool con = false;
		for (int j = 0; j < c; j++) {
			if ((same[c][j] && i != breed[j]) || (dif[c][j] && i == breed[j]) || (same[c][j] && dif[c][j])) {
				con = true;
				break;
			}
		}
		if (!con) {
			breed[c] = i;
			count += findCount(c + 1);
		}
	}
	return count;
}

int main() {
	ifstream fin("assign.in");
	fin >> N >> K;
	for (int i = 0; i < K; i++) {
		char rel;
		int c1, c2;
		fin >> rel >> c1 >> c2;
		c1--;
		c2--;
		if (rel == 'S') {
			same[c1][c2] = true;
			same[c2][c1] = true;
		}
		if (rel == 'D') {
			dif[c1][c2] = true;
			dif[c2][c1] = true;
		}
	}
	ofstream fout("assign.out");
	fout << findCount(0) << '\n';
}