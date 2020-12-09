#include <iostream>
#include <fstream>

using namespace std;

int N, M;
bool blocked[50][50];
int startcnt;
int starts[2500][2];

int main() {
	ifstream fin("crosswords.in");
	ofstream fout("crosswords.out");

	fin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			char t;
			fin >> t;
			if (t == '#') blocked[i][j] = true;
		}
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j ++) {
			if (blocked[i][j]) {
				continue;
			}
			if (i == 0 || blocked[i - 1][j]) {
				if (i < N - 2 && !blocked[i + 1][j] && !blocked[i + 2][j]) {
					starts[startcnt][0] = i;
					starts[startcnt][1] = j;
					startcnt++;
					continue;
				}
			}
			if (j == 0 || blocked[i][j - 1]) {
				if (j < M - 2 && !blocked[i][j + 1] && !blocked[i][j + 2]) {
					starts[startcnt][0] = i;
					starts[startcnt][1] = j;
					startcnt++;
					continue;
				}
			}
		}
	}
	
	fout << startcnt << '\n';
	for (int i = 0; i < startcnt; i++) {
		fout << starts[i][0] + 1 << ' ' << starts[i][1] + 1 << '\n';
	}
}