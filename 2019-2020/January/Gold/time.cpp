#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <queue>
#include <utility>
#include <string.h>

using namespace std;

struct Path {
	int c, mo, T;
};

int N, M, C;
int m[1000];
int btimes[2][1000];
vector<vector<int>> con;

int main() {
	memset(btimes, -1, sizeof(btimes));

	ifstream fin("time.in");
	ofstream fout("time.out");

	fin >> N >> M >> C;
	con.resize(N);
	for (int i = 0; i < N; i++) fin >> m[i];
	for (int i = 0; i < M; i++) {
		int a, b;
		fin >> a >> b;
		a--, b--;
		con[a].push_back(b);
	}
	
	btimes[0][0] = 0;
	int ans = 0;
	for (int i = 1; i < 1000; i++) {
		int p = i % 2;
		memset(btimes[p], -1, N * sizeof(int));
		for (int a = 0; a < N; a++) {
			if (btimes[1 - p][a] < 0) continue;
			for (int j = 0; j < con[a].size(); j++) {
				int np = con[a][j];
				btimes[p][np] = max(btimes[p][np], btimes[1 - p][a] + m[a]);
			}
		}
		ans = max(ans, btimes[p][0] - C * i * i);
	}
	fout << ans << '\n';
}