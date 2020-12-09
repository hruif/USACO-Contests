#include <iostream>
#include <fstream>
#include <algorithm>
#include <string.h>

using namespace std;

struct cow {
	int x;
	char b;
	bool operator<(const cow c) const {
		return x < c.x;
	}
};

int N;
cow cows[100005];
int dists[200005][2];

int main() {
	ifstream fin("fairphoto.in");
	ofstream fout("fairphoto.out");

	fin >> N;
	for (int i = 0; i < N; i++) {
		fin >> cows[i].x >> cows[i].b;
	}
	sort(cows, cows + N);

	int l = 0;
	int maxdist = 0;
	for (int i = 0; i < N; i++) {
		if (cows[i].b != cows[l].b) {
			l = i;
		}
		int dist = cows[i].x - cows[l].x;
		if (dist > maxdist) maxdist = dist;
	}

	memset(dists, -1, sizeof(dists));
	int val = 0;
	dists[N][0] = 0;
	for (int i = 0; i < N; i++) {
		if (cows[i].b == 'G') val++;
		else val--;
		if (dists[val + N][0] == -1) dists[val + N][0] = i + 1;
		else dists[val + N][1] = i;
	}

	for (int i = 0; i < N * 2 + 1; i++) {
		if (dists[i][1] == -1 || dists[i][0] == -1 || dists[i][0] == N) continue;
		int dist = cows[dists[i][1]].x - cows[dists[i][0]].x;
		if (dist > maxdist) maxdist = dist;
	}
	fout << maxdist << '\n';
}