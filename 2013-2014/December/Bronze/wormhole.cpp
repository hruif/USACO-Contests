#include <iostream>
#include <fstream>
#include <vector>
#include <string.h>

using namespace std;

int N;
int wh[12][2];
vector<int> goTo[12];
int onRight[12];
int pairs[12];

bool visited[12];
bool loop() {
	for (int i = 0; i < N; i++) {
		memset(visited, false, sizeof(visited));
		int w = i;
		int loop = false;
		while (true) {
			visited[w] = true;
			if (onRight[w] == -1) {
				break;
			}
			w = pairs[onRight[w]];
			if (visited[w]) {
				return true;
			}
		}
	}
	return false;
}

int pairSolve(int f) {
	bool allPaired = true;
	for (int i = 0; i < N; i++) {
		if (pairs[i] == -1) {
			allPaired = false;
			break;
		}
	}
	if (allPaired) {
		if (loop()) {
			return 1;
		}
		else {
			return 0;
		}
	}

	int total = 0;
	for (int i = f + 1; i < N - 1; i++) {
		if (pairs[i] != -1) {
			continue;
		}
		for (int j = i + 1; j < N; j++) {
			if (pairs[j] != -1) {
				continue;
			}
			pairs[i] = j;
			pairs[j] = i;
			total += pairSolve(i);
			pairs[i] = -1;
			pairs[j] = -1;
		}
	}
	return total;
}

int main() {
	ifstream fin("wormhole.in");
	fin >> N;
	for (int i = 0; i < N; i++) {
		fin >> wh[i][0] >> wh[i][1];
	}
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (j == i) {
				continue;
			}
			if (wh[i][1] == wh[j][1] && wh[i][0] < wh[j][0]) {
				goTo[i].push_back(j);
			}
		}
	}
	memset(onRight, -1, sizeof(onRight));
	for (int i = 0; i < N; i++) {
		int min = -1;
		int mini;
		if (goTo[i].size() == 0) {
			onRight[i] = -1;
		}
		else {
			for (int j = 0; j < goTo[i].size(); j++) {
				int nwh = goTo[i][j]; // next wormhole
				if (wh[nwh][0] < min || min == -1) {
					min = wh[nwh][0];
					mini = nwh;
				}
			}
			onRight[i] = mini;
		}
	}
	memset(pairs, -1, sizeof(pairs));
	int total = pairSolve(-1);
	ofstream fout("wormhole.out");
	fout << total << '\n';
}