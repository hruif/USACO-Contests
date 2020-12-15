#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

struct xs {
	int ind;
	int x;
	bool operator<(const xs a) const {
		return x < a.x;
	}
};

struct ys {
	int ind;
	int y;
	bool operator<(const ys a) const {
		return y < a.y;
	}
};

int N;
int minar;
xs sx[50000];
ys sy[50000];
int cows[50000][2];
bool removed[50000];

void checkar() {
	int fx = 0, lx = N - 1;
	int fy = 0, ly = N - 1;

	for (int i = 0; i < N; i++) {
		fx = i;
		if (!removed[sx[i].ind]) break;
	}
	for (int i = 0; i < N; i++) {
		fy = i;
		if (!removed[sy[i].ind]) break;
	}
	for (int i = N - 1; i >= 0; i--) {
		lx = i;
		if (!removed[sx[i].ind]) break;
	}
	for (int i = N - 1; i >= 0; i--) {
		ly = i;
		if (!removed[sy[i].ind]) break;
	}
	int newar = (cows[sx[lx].ind][0] - cows[sx[fx].ind][0]) * (cows[sy[ly].ind][1] - cows[sy[fy].ind][1]);
	minar = min(minar, newar);
}

void remac(int cleft) {
	if (cleft == 0) {
		checkar();
		return;
	}

	int fx = 0, lx = N - 1;
	int fy = 0, ly = N - 1;

	for (int i = 0; i < N; i++) {
		fx = i;
		if (!removed[sx[i].ind]) break;
	}
	for (int i = 0; i < N; i++) {
		fy = i;
		if (!removed[sy[i].ind]) break;
	}
	for (int i = N - 1; i >= 0; i--) {
		lx = i;
		if (!removed[sx[i].ind]) break;
	}
	for (int i = N - 1; i >= 0; i--) {
		ly = i;
		if (!removed[sy[i].ind]) break;
	}

	cleft--;

	removed[sx[fx].ind] = true;
	remac(cleft);
	removed[sx[fx].ind] = false;

	removed[sx[lx].ind] = true;
	remac(cleft);
	removed[sx[lx].ind] = false;

	removed[sy[fy].ind] = true;
	remac(cleft);
	removed[sy[fy].ind] = false;

	removed[sy[ly].ind] = true;
	remac(cleft);
	removed[sy[ly].ind] = false;
}

int main() {
	ifstream fin("reduce.in");
	ofstream fout("reduce.out");

	fin >> N;
	for (int i = 0; i < N; i++) {
		fin >> cows[i][0] >> cows[i][1];
		sx[i].ind = i;
		sy[i].ind = i;

		sx[i].x = cows[i][0];
		sy[i].y = cows[i][1];
	}
	sort(sx, sx + N);
	sort(sy, sy + N);
	minar = (sx[N - 1].x - sx[0].x) * (sy[N - 1].y - sy[0].y);
	remac(3);

	fout << minar << '\n';
}