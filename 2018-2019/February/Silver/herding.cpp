#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

int N;
int gs[100000];
int gaps[100000];
int cows[100000];

int main() {
	ifstream fin("herding.in");
	ofstream fout("herding.out");

	fin >> N;
	for (int i = 0; i < N; i++) {
		fin >> cows[i];
	}
	sort(cows, cows + N);

	int minmoves = 0;
	int maxmoves = cows[N - 1] - cows[0] - (N - 2) - min(cows[1] - cows[0], cows[N - 1] - cows[N - 2]);
	if (cows[N - 1] - cows[0] == N) {
		minmoves = 1;
	}
	else if (cows[N - 1] - cows[0] > N) {
		int maxg = 0;
		int g = 0;
		bool space = false;
		int ng = 0;
		for (int i = 0; i < N; i++) {
			if (i > 0 && cows[i - 1] != cows[i] - 1) {
				if (cows[i - 1] == cows[i] - 2) {
					space = true;
				}
				else {
					maxg = max(g, maxg);
					gs[ng++] = g;
					g = 0;
				}
			}
			else g++;
		}
		gs[ng++] = g;
		if (ng == 2 && (gs[0] == 1 || gs[1] == 1)) {
			if (space) minmoves = 1;
			else minmoves = 2;
		}
		else {
			minmoves = N - maxg;
		}
	}

	fout << minmoves << '\n'
		<< maxmoves << '\n';
}