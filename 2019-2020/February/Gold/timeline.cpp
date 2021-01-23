#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <string.h>
#include <algorithm>

using namespace std;

int N, M, C;
int S[100000];
vector<vector<pair<int, int>>> aft;
int minoccs[100000];

int findminocc(int ind) {
	if (minoccs[ind] != -1) return minoccs[ind];
	int minocc = S[ind];
	for (int i = 0; i < aft[ind].size(); i++) {
		minocc = max(minocc, findminocc(aft[ind][i].first) + aft[ind][i].second);
	}
	minoccs[ind] = minocc;
	return minocc;
}

int main() {
	memset(minoccs, -1, sizeof(minoccs));

	ifstream fin("timeline.in");
	ofstream fout("timeline.out");

	fin >> N >> M >> C;
	aft.resize(N);
	for (int i = 0; i < N; i++) fin >> S[i];
	for (int i = 0; i < C; i++) {
		int a, b, x;
		fin >> a >> b >> x;
		a--, b--;
		aft[b].push_back(make_pair(a, x));
	}

	for (int i = 0; i < N; i++) {
		fout << findminocc(i) << '\n';
	}
}