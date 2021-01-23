#include <iostream>
#include <fstream>
#include <algorithm>
#include <queue>
#include <vector>

#define ll long long
#define MOD (ll)(1e9 + 7)

using namespace std;

int N, M, K;
vector<ll> dp;
queue<ll> sums;

int main() {
	ifstream fin("spainting.in");
	ofstream fout("spainting.out");

	fin >> N >> M >> K;
	dp.resize(N + 1);

	dp[K] = 1;
	ll dpsum = 0;
	ll mval = 1;
	for (int n = K + 1; n <= N; n++) {
		dpsum = (dpsum + dp[n - 1] + mval) % MOD;
		if (n - K >= K) {
			dpsum = (dpsum + MOD - dp[n - K]) % MOD;
		}
		dp[n] = (dpsum * (M - 1) + 1) % MOD;
		mval = mval * M % MOD;
	}
	ll ans = dp[N] * M;

	fout << ans % MOD << '\n';
}