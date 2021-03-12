#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <utility>
#include <algorithm>
#include <string.h>

#define pii pair<int, int>

using namespace std;

int N, K;
int par[50000];
vector<int> b, btimes;
vector<vector<int>> comm;
vector<vector<bool>> mat;

int main() {
	cin >> N >> K;
	b.resize(N); btimes.resize(N, -1);
	comm.resize(K);
	mat.resize(K, vector<bool>(K, false));
	for (int i = 0; i < N; i++) {
		cin >> b[i];
		b[i]--;
	}
	for (int i = 0; i < K; i++) {
		for (int j = 0; j < K; j++) {
			char val;
			cin >> val;
			if (val == '1') mat[i][j] = true;
		}
	}
	for (int i = 0; i < K; i++) {
		for (int j = 0; j < N; j++) {
			if (mat[i][b[j]]) comm[i].push_back(j);
		}
	}

	int ans = -1;
	priority_queue<pair<int, int>, vector<pii>, greater<pii>> q;
	q.push({ 0, N });
	while (!q.empty()) {
		pair<int, int> p = q.top();
		q.pop();
		int time = p.first, ind = N - p.second;
		int breed = b[ind];
		if (time > btimes[ind] && btimes[ind] != -1) {
			continue;
		}
		if (ind == N - 1) {
			if (time < ans || ans == -1) ans = time;
			continue;
		}
		btimes[ind] = time;

		for (int i = 0; i < comm[breed].size(); i++) {
			int nind = comm[breed][i];
			if (ind == nind) continue;
			pair<int, int> np{ time, N - nind };
			if (ind > nind) np.first += ind - nind;
			if (np.first < btimes[nind] || btimes[nind] == -1) {
				btimes[nind] = np.first;
				par[nind] = breed;
				q.push(np);
			}
			else if (par[nind] == breed) break;
		}
	}
	if (ans == -1) cout << "-1\n";
	else cout << ans * 2 + N - 1 << '\n';
}