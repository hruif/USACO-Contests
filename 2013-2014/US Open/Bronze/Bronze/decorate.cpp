#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int N, M;
char C[50005];
vector<vector<int>> paths;

int cnt[3];
bool dfs(int ci) {
	int nl = 3 - C[ci];
	for (int i = 0; i < paths[ci].size(); i++) {
		int nci = paths[ci][i];
		if (C[nci] == 0) {
			C[nci] = nl;
			cnt[nl]++;
			if (!dfs(nci)) return false;
		}
		else if (C[nci] != nl) {
			return false;
		}
	}
	return true;
}

int main() {
	ifstream fin("decorate.in");
	ofstream fout("decorate.out");

	fin >> N >> M;
	paths.resize(N);
	for (int i = 0; i < M; i++) {
		int A, B;
		fin >> A >> B;
		paths[A - 1].push_back(B - 1);
		paths[B - 1].push_back(A - 1);
	}

	int total = 0;
	bool impossible = false;
	for (int i = 0; i < N; i++) {
		if (C[i] != 0) continue;

		cnt[1] = 1;
		cnt[2] = 0;
		C[i] = 1;
		if (!dfs(i)) {
			impossible = true;
			break;
		}
		total += max(cnt[1], cnt[2]);
	}

	if (impossible) {
		fout << -1 << '\n';
	}
	else {
		fout << total << '\n';
	}
}