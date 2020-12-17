#include <iostream>
#include <fstream>
#include <string.h>
#include <algorithm>

using namespace std;

int N;
int ps[200][3];
bool visited[200];

bool indist(int trans, int rec) {
	int xdist = abs(ps[trans][0] - ps[rec][0]);
	int ydist = abs(ps[trans][1] - ps[rec][1]);
	double dist = sqrt(xdist * xdist + ydist * ydist);
	return dist <= ps[trans][2];
}

void findcows(int ind) {
	visited[ind] = true;
	for (int i = 0; i < N; i++) {
		if (visited[i]) continue;
		if (indist(ind, i)) findcows(i);
	}
}

int main() {
	ifstream fin("moocast.in");
	ofstream fout("moocast.out");

	fin >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < 3; j++) fin >> ps[i][j];
	}

	int maxcows = 0;
	for (int i = 0; i < N; i++) {
		memset(visited, false, sizeof(visited));

		findcows(i);
		int cows = 0;
		for (int j = 0; j < N; j++) {
			if (visited[j]) cows++;
		}

		if (cows > maxcows) maxcows = cows;
	}

	fout << maxcows << '\n';
}