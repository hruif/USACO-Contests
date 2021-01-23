#include <iostream>
#include <fstream>
#include <queue>

using namespace std;

struct St {
	int x1, y1, d1;
	int x2, y2, d2;
	int sl; // sequence length
};

int N;
char barn[20][20];
bool states[20][20][4][20][20][4]; //[x1][y1][dir1][x2][y2][dir2]
queue<St> paths;

int main() {
	ifstream fin("cownav.in");
	ofstream fout("cownav.out");

	fin >> N;
	for (int i = N - 1; i >= 0; i--) {
		for (int j = 0; j < N; j++) {
			fin >> barn[i][j];
		}
	}

	St start{ 0, 0, 0, 0, 0, 1, 0 };
	paths.push(start);
	int ans = -1;
	while (!paths.empty()) {
		St cur = paths.front();
		paths.pop();
		int x1 = cur.x1, y1 = cur.y1, d1 = cur.d1;
		int x2 = cur.x2, y2 = cur.y2, d2 = cur.d2;
		int sl = cur.sl;
		if (x1 == N - 1 && y1 == N - 1 && x2 == N - 1 && y2 == N - 1) {
			ans = sl;
			break;
		}
		if (states[x1][y1][d1][x2][y2][d2]) continue;
		states[x1][y1][d1][x2][y2][d2] = true;
		St next{ x1, y1, d1, x2, y2, d2, sl + 1 };
		next.d1 = (d1 + 1) % 4, next.d2 = (d2 + 1) % 4;
		if (!states[x1][y1][next.d1][x2][y2][next.d2]) paths.push(next);
		next.d1 = (d1 + 3) % 4, next.d2 = (d2 + 3) % 4;
		if (!states[x1][y1][next.d1][x2][y2][next.d2]) paths.push(next);
		next.d1 = d1, next.d2 = d2;
		int nx = x1, ny = y1;
		if (x1 != N - 1 || y1 != N - 1) {
			switch (d1) {
			case 0: ny++; break;
			case 1: nx++; break;
			case 2: ny--; break;
			case 3: nx--; break;
			}
			if (!(nx < 0 || nx >= N || ny < 0 || ny >= N
				|| barn[nx][ny] == 'H')) {
				next.x1 = nx;
				next.y1 = ny;
			}
		}
		nx = x2, ny = y2;
		if (x2 != N - 1 || y2 != N - 1) {
			switch (d2) {
			case 0: ny++; break;
			case 1: nx++; break;
			case 2: ny--; break;
			case 3: nx--; break;
			}
			if (!(nx < 0 || nx >= N || ny < 0 || ny >= N
				|| barn[nx][ny] == 'H')) {
				next.x2 = nx;
				next.y2 = ny;
			}
		}
		if (!states[next.x1][next.y1][d1][next.x2][next.y2][d2]) paths.push(next);
	}

	fout << ans << '\n';
}