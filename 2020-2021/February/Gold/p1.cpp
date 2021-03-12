#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <climits>
#include <algorithm>

#define ll long long

using namespace std;

int N;
int a[100000];
int dp[1000002];

int lbinds[1000002];
int ubinds[1000002];

int main() {
	dp[1000001] = 2;

	cin >> N;
	for (int i = 0; i < N; i++) cin >> a[i];
	sort(a, a + N);
	for (int i = 0; i <= 1000001; i++) lbinds[i] = lower_bound(a, a + N, i) - a;
	for (int i = 0; i <= 1000001; i++) ubinds[i] = upper_bound(a, a + N, i) - a;

	ll cnt = 0;
	int p = N - 1;
	for (int s = 1000000; s > 0; s--) {
		int scnt = ubinds[min(s * 2, 1000001)] - lbinds[s];
		int s2 = min(s * 2, 1000001);
		bool firstMoveWin = false, secondMoveWin = false; // first or second move after exhausting all numbers that divide to one
		{
			if (lbinds[s2] == N) secondMoveWin = true;
			else {
				int lb = lbinds[min(s2, 1000001)];
				while (lb != N) {
					if (dp[s2] == 1) {
						firstMoveWin = true;
						break;
					}
					lb = lbinds[s2];
				}
			}
		}
		if (firstMoveWin) {
			dp[s] = 2;
			continue;
		}
		if (scnt % 2) {
			dp[s] = 1;
			cnt += scnt;
		}
		else {
			dp[s] = 2;
		}
	}
	cout << cnt << '\n';
}