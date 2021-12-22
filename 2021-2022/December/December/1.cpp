#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <cstring>
#include <utility>

using namespace std;
using ll = long long;

const int MAX_N = 100000;

int T, N, K;
ll x[MAX_N], y[MAX_N];
vector<pair<ll, int>> cows;
ll dp[MAX_N][2];

int main() {
	cin >> T >> N >> K;
	for (int i = 0; i < N; i++) cin >> x[i] >> y[i];
	for (int i = 0; i < N; i++) cows.push_back({ x[i], y[i] });
	for (int i = 0; i < N; i++) {
		ll pos = cows[i].first, weight = cows[i].second;
		int ind = (upper_bound(cows.begin(), cows.end(), make_pair(pos - K, -1)) - cows.begin()) - 1;
		if (ind < 0) {
			if (i == 0) dp[i][0] = weight;
			else {
				if (T == 2) {
					if (i % 2 == 0) dp[i][0] = max(dp[i - 2][0], weight);
				}
				else {
					if (i % 2) dp[i][0] = min(dp[i - 2][0], weight);
				}
			}
		}
		else {
			if (i == N - 1) 

			ll dif = pos - cows[ind].first - 1;

		}
	}
	cout << dp[N - 1][0] << '\n';
}