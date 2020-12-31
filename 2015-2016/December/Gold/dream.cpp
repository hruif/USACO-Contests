#include <iostream>
#include <fstream>
#include <algorithm>
#include <string.h>
#include <queue>

#define INF 10000001

using namespace std;

struct Point {
	int x;
	int y;
	bool oj;
	int dir;
	int moves;
	Point() {}
	Point(int x, int y, bool oj, int dir, int moves) {
		this->x = x;
		this->y = y;
		this->oj = oj;
		this->dir = dir;
		this->moves = moves;
	}
};

int N, M;
int maze[1000][1000];
bool bps[1000][1000][2][4];

int main() {
	ifstream fin("dream.in");
	ofstream fout("dream.out");

	fin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			fin >> maze[i][j];
		}
	}

	int ans = -1;
	queue<Point> ps;
	ps.push(Point(0, 0, false, 1, 0));
	while (!ps.empty()) {
		Point p = ps.front();
		int x = p.x, y = p.y, dir = p.dir, moves = p.moves;
		if (x == N - 1 && y == M - 1) {
			ans = p.moves;
			break;
		}
		ps.pop();
		if (x < 0 || x >= N || y < 0 || y >= M) continue;
		if (maze[x][y] == 0) continue;
		if (maze[x][y] == 2) p.oj = true;
		if (maze[x][y] == 3 && !p.oj) continue;
		if (maze[x][y] == 4) p.oj = false;
		if (bps[x][y][p.oj][dir]) continue;
		bps[x][y][p.oj][dir] = true;

		if (maze[p.x][p.y] == 4) {
			int newx = x, newy = y;
			switch (dir) {
			case 0: newx--; break;
			case 1: newy++; break;
			case 2: newx++; break;
			case 3: newy--; break;
			}

			if (newx >= 0 && newx < N && newy >= 0 && newy < M
				&& maze[newx][newy] != 0 && maze[newx][newy] != 3) {
				ps.push(Point(newx, newy, p.oj, dir, moves + 1));
				continue;
			}
		}
		ps.push(Point(x - 1, y, p.oj, 0, moves + 1));
		ps.push(Point(x, y + 1, p.oj, 1, moves + 1));
		ps.push(Point(x + 1, y, p.oj, 2, moves + 1));
		ps.push(Point(x, y - 1, p.oj, 3, moves + 1));
	}

	fout << ans << '\n';
}