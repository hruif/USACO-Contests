#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

int N, K;
int ds[50000];
int maxf[50000];
int maxs[50000];

int main() {
	ifstream fin("diamond.in");
	ofstream fout("diamond.out");

	fin >> N >> K;
	for (int i = 0; i < N; i++) {
		fin >> ds[i];
	}
	sort(ds, ds + N);

	int rp = 0;
	for (int i = 0; i < N; i++) {
		while (ds[rp] - ds[i] <= K && rp < N) rp++;
		maxf[i] = rp - i;
	}
	int maxss = 0;
	for (int i = N - 1; i >= 0; i--) {
		if (maxf[i] > maxss) maxss = maxf[i];
		maxs[i] = maxss;
	}

	int bests = 0;
	for (int i = 0; i < N - 1; i++) {
		int s1 = maxf[i];
		int s2 = maxs[i + s1];
		int ts = s1 + s2;
		if (ts > bests) bests = ts;
	}

	fout << bests << '\n';
}