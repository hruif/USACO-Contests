#include <iostream>
#include <fstream>
#include <queue>

#define INF (ll)(1e18)
#define ll long long

using namespace std;

struct Path {
	int x, y, m;
	ll et;
};

int N, T;
int field[100][100];
ll btimes[100][100][3];
queue<Path> paths;

int main() {
	for (int i = 0; i < 100; i++) {
		for (int j = 0; j < 100; j++) {
			for (int k = 0; k < 3; k++) {
				btimes[i][j][k] = INF;
			}
		}
	}

	ifstream fin("visitfj.in");
	ofstream fout("visitfj.out");

	fin >> N >> T;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			fin >> field[i][j];
		}
	}

	Path start{ 0, 0, 0, 0 };
	paths.push(start);
	while (!paths.empty()) {
		Path cur = paths.front();
		paths.pop();
		int x = cur.x, y = cur.y, m = cur.m;
		ll t = cur.et;
		if (btimes[x][y][m % 3] < t) continue;
		btimes[x][y][m % 3] = t;
		bool eat = (m + 1) % 3 == 0 && m != 0;
		if (x > 0) {
			Path next{ x - 1, y, m + 1, t + T };
			if (eat) next.et += field[next.x][next.y];
			if (btimes[next.x][next.y][next.m % 3] > next.et) {
				paths.push(next);
				btimes[next.x][next.y][next.m % 3] = next.et;
			}
		}
		if (y > 0) {
			Path next{ x, y - 1, m + 1, t + T };
			if (eat) next.et += field[next.x][next.y];
			if (btimes[next.x][next.y][next.m % 3] > next.et) {
				paths.push(next);
				btimes[next.x][next.y][next.m % 3] = next.et;
			}
		}
		if (x < N - 1) {
			Path next{ x + 1, y, m + 1, t + T };
			if (eat) next.et += field[next.x][next.y];
			if (btimes[next.x][next.y][next.m % 3] > next.et) {
				paths.push(next);
				btimes[next.x][next.y][next.m % 3] = next.et;
			}
		}
		if (y < N - 1) {
			Path next{ x, y + 1, m + 1, t + T };
			if (eat) next.et += field[next.x][next.y];
			if (btimes[next.x][next.y][next.m % 3] > next.et) {
				paths.push(next);
				btimes[next.x][next.y][next.m % 3] = next.et;
			}
		}
	}
	fout << min(btimes[N - 1][N - 1][0], min(btimes[N - 1][N - 1][1], btimes[N - 1][N - 1][2])) << '\n';
}