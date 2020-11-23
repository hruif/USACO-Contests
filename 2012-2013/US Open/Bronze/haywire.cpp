#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

int N;
int rels[12][3];
int pos[12];

bool checked[12][3];
int findLen() {
	memset(checked, 0, sizeof(checked));
	int totalLen = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < 3; j++) {
			if (!checked[i][j]) {
				checked[i][j] = true;
				int ind;
				int r = rels[i][j];
				for (int k = 0; k < 3; k++) {
					if (rels[r][k] == i) {
						ind = k;
						break;
					}
				}
				checked[r][ind] = true;
				totalLen += abs(pos[i] - pos[r]);
			}
		}
	}
	return totalLen;
}

bool visited[12];
int findLow(int p, int max) {
	if (p == max) {
		return findLen();
	}
	int low = -1;
	for (int i = 0; i < N; i++) {
		if (visited[i]) {
			continue;
		}
		pos[i] = p;
		visited[i] = true;
		int tlow = findLow(p + 1, max);
		if (tlow < low || low == -1) {
			low = tlow;
		}
		visited[i] = false;
	}
	return low;
}

int back4() {
	int low = -1;
	for (int i = 0; i < N; i++) {
		if (visited[i]) {
			continue;
		}
		pos[i] = N - 1;
		visited[i] = true;
		for (int j = 0; j < 3; j++) {
			int r1 = rels[i][j];
			if (visited[r1]) {
				continue;
			}
			pos[r1] = N - 2;
			visited[r1] = true;
			for (int k = 0; k < 3; k++) {
				if (j == k) {
					continue;
				}
				int r2 = rels[i][k];
				if (visited[r2]) {
					continue;
				}
				pos[r2] = N - 3;
				visited[r2] = true;
					int tlow = findLow(3, N - 3);
					if (tlow < low || low == -1) {
						low = tlow;
					}
				visited[r2] = false;
			}
			visited[r1] = false;
		}
		visited[i] = false;
	}
	return low;
}

int front4() {
	int low = -1;
	for (int i = 0; i < N; i++) {
		if (visited[i]) {
			continue;
		}
		pos[i] = 0;
		visited[i] = true;
		for (int j = 0; j < 3; j++) {
			int r1 = rels[i][j];
			if (visited[r1]) {
				continue;
			}
			pos[r1] = 1;
			visited[r1] = true;
			for (int k = 0; k < 3; k++) {
				if (j == k) {
					continue;
				}
				int r2 = rels[i][k];
				if (visited[r2]) {
					continue;
				}
				pos[r2] = 2;
				visited[r2] = true;
					int tlow = back4();
					if (tlow < low || low == -1) {
						low = tlow;
					}
				visited[r2] = false;
			}
			visited[r1] = false;
		}
		visited[i] = false;
	}
	return low;
}

int main() {
	ifstream fin("haywire.in");
	fin >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < 3; j++) {
			fin >> rels[i][j];
			rels[i][j]--;
		}
	}
	int ans;
	if (N < 8) {
		ans = findLow(0, N);
	}
	else {
		ans = front4();
	}
	ofstream fout("haywire.out");
	fout << ans << '\n';
}