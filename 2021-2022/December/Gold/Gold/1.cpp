#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <cstring>
#include <utility>

using namespace std;
using ll = long long;

const ll inf = 100000000000000000;
const int MAX_N = 100000;

int T, N, K;
ll x[MAX_N], y[MAX_N];
vector<pair<ll, int>> cows;
ll dp[MAX_N][2][2]; // [paired ? 0 : 1][even ? 0 : 1]

ll cmp(ll a, ll b, ll t) {
	if (t == 1) return min(a, b);
	else return max(a, b);
}

int main() {

	cin >> T >> N >> K;
	for (int i = 0; i < N; i++) cin >> x[i] >> y[i];
	for (int i = 0; i < N; i++) cows.push_back({ x[i], y[i] });
	sort(cows.begin(), cows.end());
	ll c = cmp(-inf, inf, T), r = cmp(-inf, inf, 3 - T);
	for (int i = 0; i < MAX_N; i++) for (int j = 0; j < 2; j++) for (int k = 0; k < 2; k++) dp[i][j][k] = r;
	for (int i = 0; i < N; i++) {
		int b = upper_bound(cows.begin(), cows.end(), make_pair(x[i] - K, -1)) - cows.begin();
		if (b == i) {
			if (i == 0) {
				dp[i][0][1] = 0;
				dp[i][1][0] = cows[i].second;
			}
			else {
				dp[i][0][1] = cmp(dp[i - 1][0][0], dp[i - 1][1][0], T);
				dp[i][1][0] = cmp(dp[i - 1][0][0], dp[i - 1][1][0], T) + cows[i].second;
			}
		}
		else {
			dp[i][0][0] = dp[i - 1][1][1];
			dp[i][0][1] = dp[i - 1][1][0];
			dp[i][0][0] = cmp(dp[i][0][0], dp[i - 1][0][1], T);
			dp[i][0][1] = cmp(dp[i][0][1], dp[i - 1][0][0], T);
			int d = (i - b) % 2;

			dp[i][1][0] = cmp(dp[i][1][0], dp[b][0][1 - d] + cows[i].second, T);
			if (i + 1 == N || cows[i + 1].first - cows[i - 1].first <= K) 
				dp[i][1][1] = cmp(dp[i][1][1], dp[b][0][d] + cows[i].second, T);

		}
	}
	cout << cmp(dp[N - 1][0][0], dp[N - 1][1][0], T) << '\n';
}