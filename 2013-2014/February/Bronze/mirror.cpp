#include <iostream>
#include <fstream>
#include <string.h>
#include <algorithm>

using namespace std;

int N, M;
char field[1000][1000];
int len[1000][1000][4];
bool loop = false;
int countt = 0;

int dirtodir(int x, int y, int dir) {
	if (field[x][y] == '/') {
		switch (dir) {
		case 0:
			return 1;
		case 1:
			return 0;
		case 2:
			return 3;
		case 3:
			return 2;
		}
	}
	else {
		switch (dir) {
		case 0:
			return 3;
		case 1:
			return 2;
		case 2:
			return 1;
		case 3:
			return 0;
		}
	}
}

int findpath(int x, int y, int dir) {
	int pathlen = 0;
	while (x >= 0 && x < N && y >= 0 && y < M) {
		countt++;
		len[x][y][(dir + 2) % 4] = pathlen;
		dir = dirtodir(x, y, dir);
		if (len[x][y][dir] != -1) {
			return len[x][y][dir] + pathlen;
		}
		switch (dir) {
		case 0:
			x--;
			break;
		case 1:
			y++;
			break;
		case 2:
			x++;
			break;
		case 3:
			y--;
			break;
		}
		pathlen++;
	}
	return pathlen;
}

int main() {
	memset(len, -1, sizeof(len));

	ifstream fin("mirror.in");
	fin >> N >> M;
	for (int i = 0; i < N; i++) {
		fin >> field[i];
	}
	int maxpath = 0;
	for (int i = 0; i < N; i++) {
		int l, r;
		l = findpath(i, 0, 1);
		r = findpath(i, M - 1, 3);
		maxpath = max(maxpath, max(l, r));
	}
	for (int i = 0; i < M; i++) {
		int t, b;
		t = findpath(0, i, 2);
		b = findpath(N - 1, i, 0);
		maxpath = max(maxpath, max(t, b));
	}
	ofstream fout("mirror.out");
	if (loop) {
		fout << "-1\n";
	}
	else {
		fout << maxpath << '\n';
	}
	cout << countt;
}