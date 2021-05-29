#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;
using ll = long long;

#define MOD (ll)(1e9 + 7)

int K;
int N[50000], M[50000], maxn;
vector<vector<vector<int>>> edges;
vector<vector<int>> even, odd, larger;

void findEvenOdd(int graph) {
	int n = N[graph], m = M[graph];

	vector<vector<int>> e;
	vector<int> dists(n * 2, -1);
	e.resize(n * 2);
	for (int i = 0; i < n; i++) {
		for (auto j : edges[graph][i]) {
			e[i].push_back(j + n);
			e[i + n].push_back(j);
		}
	}

	queue<int> q;
	q.push(0);
	dists[0] = 0;
	while (!q.empty()) {
		int node = q.front();
		q.pop();

		for (auto i : e[node]) {
			if (dists[i] == -1) {
				dists[i] = dists[node] + 1;
				q.push(i);
			}
		}
	}

	even[graph].resize(n); odd[graph].resize(n);
	larger[graph].resize(n);
	for (int i = 0; i < n; i++) {
		even[graph][i] = dists[i];
	}
	for (int i = 0; i < n; i++) {
		odd[graph][i] = dists[i + n];
	}
	for (int i = 0; i < n; i++) {
		int ev = even[graph][i], od = odd[graph][i];
		larger[graph][i] = max(ev, od);
		if (ev == -1 || od == -1) larger[graph][i] = -1;
	}
}

ll compute_sum(vector<vector<int>>& dists) {
	vector<ll> less(maxn * 2);

	vector<ll> prefix(maxn * 2, 1);
	vector<ll> suffix(maxn * 2, 1);
	for (int i = 0; i < K; i++) {
		sort(dists[i].begin(), dists[i].end());
		int p = lower_bound(dists[i].begin(), dists[i].end(), 0) - dists[i].begin();
		int x = 0;
		int cnt = 0;
		while (p < N[i]) {
			while (p < N[i] && x == dists[i][p]) {
				cnt++;
				p++;
			}
			prefix[x] *= cnt;
			prefix[x] %= MOD;
			x++;
		}
		suffix[dists[i][N[i] - 1] + 1] *= cnt;
		suffix[dists[i][N[i] - 1] + 1] %= MOD;
	}
	for (int i = 1; i < maxn * 2; i++) {
		suffix[i] *= suffix[i - 1];
		suffix[i] %= MOD;
	}

	for (int i = 0; i < maxn * 2; i++) {
		less[i] = prefix[i] * suffix[i];
		less[i] %= MOD;
	}
	
	ll sum = 0;
	for (int i = 1; i < maxn * 2; i++) {
		sum += (less[i] - less[i - 1]) * i;
	}
	return sum % MOD;
}

int main() {
	cin >> K;
	edges.resize(K);
	even.resize(K); odd.resize(K); larger.resize(K);
	for (int i = 0; i < K; i++) {
		cin >> N[i] >> M[i];
		maxn = max(maxn, N[i]);
		edges[i].resize(N[i]);
		for (int j = 0; j < M[i]; j++) {
			int a, b;
			cin >> a >> b;
			a--; b--;
			edges[i][a].push_back(b);
			if (a != b) edges[i][b].push_back(a);
		}
	}

	for (int i = 0; i < K; i++) findEvenOdd(i);

	cout << (compute_sum(even) + compute_sum(odd) + MOD - compute_sum(larger)) % MOD << '\n';
}