#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

struct Path {
	int c, mo, T;
};

int N, M, C;
int m[1000];
int btimes[1000][1000];
vector<vector<int>> con;
vector<vector<int>> sts;

int main() {
	ifstream fin("time.in");
	ofstream fout("time.out");

	fin >> N >> M >> C;
	con.resize(N);
	for (int i = 0; i < N; i++) for (int j = 0; j < 1000; j++) btimes[i][j] = -1000000000;
	//btimes.resize(N, vector<int>(1000, -1000000000));
	//sts.resize(N, vector<int>(2048, 0));
	for (int i = 0; i < N; i++) fin >> m[i];
	for (int i = 0; i < M; i++) {
		int a, b;
		fin >> a >> b;
		a--, b--;
		con[a].push_back(b);
	}
	
	queue<Path> paths;
	paths.push(Path{ 0, 0, 0 });
	while (!paths.empty()) {
		Path p = paths.front();
		paths.pop();
		int c = p.c, mo = p.mo, T = p.T;
		if (mo <= btimes[c][T]) continue;
		btimes[c][T] = mo;
		if (T >= 999) continue;
		for (int i = 0; i < con[c].size(); i++) {
			int next = con[c][i];
			int nextmo = mo + m[next];
			if (nextmo > btimes[next][T + 1]) {
				paths.push({ next, nextmo, T + 1 });
			}
		}
	}
	int ans = 0;
	for (int i = 0; i < 1000; i++) {
		ans = max(ans, btimes[0][i] - (C * i * i));
	}
	fout << ans << '\n';
}