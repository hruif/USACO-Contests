#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

int N, L;
int knots[100];
int spaces[99];
int ans = 0;

bool canFold(int l, int r) {
	while (l >= 0 && r < N - 1) {
		if (spaces[l--] != spaces[r++]) {
			return false;
		}
	}
	return true;
}

int main() {
	ifstream fin("folding.in");
	fin >> N >> L;
	for (int i = 0; i < N; i++) {
		fin >> knots[i];
	}
	sort(knots, knots + N);
	for (int i = 0; i < N - 1; i++) {
		spaces[i] = knots[i + 1] - knots[i];
	}
	for (int i = 0; i < N - 1; i++) {
		if (canFold(i - 1, i + 1)) {
			ans++;
		}
	}
	for (int i = 0; i < N - 2; i++) {
		if (canFold(i, i + 1)) {
			ans++;
		}
	}
	cout << ans << '\n';
}