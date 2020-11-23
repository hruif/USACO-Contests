#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int N, a, b;
int mirrors[501][3];
int nextMirs[501][4];
int startMir;

int newDir(int dirIn, int mir) {
	if (mir == 1) {
		switch (dirIn) {
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
		switch (dirIn) {
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

bool visited[501][4];
bool reaches(int mirflip) {
	memset(visited, 0, sizeof(visited));
	if (mirflip != -1) {
		mirrors[mirflip][2] = 1 - mirrors[mirflip][2];
	}

	int mir = startMir;
	int dir = 1;
	while (mir != -1 && mir != N) {
		if (visited[mir][dir]) {
			mir = -1;
			break;
		}
		visited[mir][dir] = true;
		dir = newDir(dir, mirrors[mir][2]);
		mir = nextMirs[mir][dir];
	}

	if (mirflip != -1) {
		mirrors[mirflip][2] = 1 - mirrors[mirflip][2];
	}

	return mir == N;
}

int main() {
	ifstream fin("input.in");
	fin >> N >> a >> b;
	for (int i = 0; i < N; i++) {
		char dir;
		fin >> mirrors[i][0] >> mirrors[i][1] >> dir;
		if (dir == '\\') {
			mirrors[i][2] = 0;
		}
		else {
			mirrors[i][2] = 1;
		}
	}
	mirrors[N][0] = a;
	mirrors[N][1] = b;
	memset(nextMirs, -1, sizeof(nextMirs));
	for (int i = 0; i < N; i++) {
		int t = -1, d = -1, l = -1, r = -1;
		for (int j = 0; j < N + 1; j++) {
			if (j == i) {
				continue;
			}
			if (mirrors[i][0] == mirrors[j][0]) {
				if (mirrors[j][1] - mirrors[i][1] > 0) {
					if (mirrors[j][1] < mirrors[t][1] || t == -1) {
						t = j;
					}
				}
				else {
					if (mirrors[j][1] > mirrors[d][1] || d == -1) {
						d = j;
					}
				}
			}
			if (mirrors[i][1] == mirrors[j][1]) {
				if (mirrors[j][0] - mirrors[i][0] > 0) {
					if (mirrors[j][0] < mirrors[r][0] || r == -1) {
						r = j;
					}
				}
				else {
					if (mirrors[j][0] > mirrors[l][0] || l == -1) {
						l = j;
					}
				}
			}
		}
		nextMirs[i][0] = t;
		nextMirs[i][1] = r;
		nextMirs[i][2] = d;
		nextMirs[i][3] = l;
	}
	for (int i = 0; i < N; i++) {
		if (mirrors[startMir][1] != 0 || mirrors[startMir][0] < 0) {
			startMir = i;
		}
		if (mirrors[i][1] == 0 && mirrors[i][0] > 0 && mirrors[i][0] < mirrors[startMir][0]) {
			startMir = i;
		}
	}
	int mir = -1;
	if (mirrors[startMir][1] != 0 || mirrors[startMir][0] < 0) {
		if (a < 0 || b != 0) {
			mir = -2;
		}
	}
	else {
		for (int i = -1; i < N; i++) {
			if (reaches(i)) {
				break;
			}
			mir++;
		}
	}
	if (mir == N) {
		mir = -2;
	}
	cout << mir + 1;
}