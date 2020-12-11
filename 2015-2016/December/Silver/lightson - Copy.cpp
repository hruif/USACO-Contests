#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

struct room {
	int x;
	int y;
	room() {}
	room(int x, int y) {
		this->x = x;
		this->y = y;
	}
};

int N, M;
bool lit[100][100];
bool pathTo[100][100];
vector<room> sw[100][100];

void findPaths(int x, int y);

void checkPathTo(int x, int y) {
	if (x > 0) {
		if (pathTo[x - 1][y]) pathTo[x][y] = true;
	}
	if (x < N - 1) {
		if (pathTo[x + 1][y]) pathTo[x][y] = true;
	}
	if (y > 0) {
		if (pathTo[x][y - 1]) pathTo[x][y] = true;
	}
	if (y < N - 1) {
		if (pathTo[x][y + 1]) pathTo[x][y] = true;
	}

	if (pathTo[x][y]) {
		if (x > 0) {
			if (lit[x - 1][y] && !pathTo[x - 1][y]) {
				checkPathTo(x - 1, y);
				findPaths(x - 1, y);
			}
		}
		if (x < N - 1) {
			if (lit[x + 1][y] && !pathTo[x + 1][y]) {
				checkPathTo(x + 1, y);
				findPaths(x + 1, y);
			}
		}
		if (y > 0) {
			if (lit[x][y - 1] && !pathTo[x][y - 1]) {
				checkPathTo(x, y - 1);
				findPaths(x, y - 1);
			}
		}
		if (y < N - 1) {
			if (lit[x][y + 1] && !pathTo[x][y + 1]) {
				checkPathTo(x, y + 1);
				findPaths(x, y + 1);
			}
		}
	}
}

void findPaths(int x, int y) {
	for (int i = 0; i < sw[x][y].size(); i++) {
		room& r = sw[x][y][i];
		lit[r.x][r.y] = true;
		if (!pathTo[r.x][r.y]) {
			checkPathTo(r.x, r.y);
		}
	}
}

int main() {
	ifstream fin("lightson.in");
	ofstream fout("lightson.out");

	fin >> N >> M;
	for (int i = 0; i < M; i++) {
		int x, y, a, b;
		fin >> x >> y >> a >> b;
		x--, y--, a--, b--;
		sw[x][y].push_back(room(a, b));
	}
	pathTo[0][0] = true;
	lit[0][0] = true;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (lit[i][j] && pathTo[i][j]) {
				findPaths(i, j);
			}
		}
	}

	int litrs = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (lit[i][j]) litrs++;
		}
	}

	fout << litrs << '\n';
}