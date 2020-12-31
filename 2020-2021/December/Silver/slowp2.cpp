#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_set>
#include <algorithm>

#define ll long long

using namespace std;

struct Point {
	int x;
	int y;
	Point() {}
	Point(int x, int y) {
		this->x = x;
		this->y = y;
	}
};

int N;
ll toignr[2500][2500];
ll abv[2500][2500];
ll bl[2500][2500];
ll dp[2500][2500];
Point cows[2500];

bool sortx(const Point a, const Point b) {
	return a.x < b.x;
}

bool sorty(const Point a, const Point b) {
	return a.y < b.y;
}

ll xs[2500];
ll ys[2500];
int main() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> cows[i].x >> cows[i].y;
		xs[i] = cows[i].x;
		ys[i] = cows[i].y;
	}
	sort(cows, cows + N, sortx);
	sort(xs, xs + N);
	sort(ys, ys + N);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (cows[i].x == xs[j]) {
				cows[i].x = j;
				break;
			}
		}
		for (int j = 0; j < N; j++) {
			if (cows[i].y == ys[j]) {
				cows[i].y = j;
				break;
			}
		}
	}
	for (int i = 0; i < N; i++) {
		dp[cows[i].x][cows[i].y]++;
	}

	for (int i = 0; i < 2500; i++) {
		bool nl = i > 0;
		for (int j = 0; j < 2500; j++) {
			bool nb = j > 0;
			if (nl) dp[i][j] += dp[i - 1][j];
			if (nb) dp[i][j] += dp[i][j - 1];
			if (nl && nb) dp[i][j] -= dp[i - 1][j - 1];
		}
	}

	for (int i = 0; i < N - 1; i++) {
		int x1 = cows[i].x, y1 = cows[i].y;
		for (int j = i + 1; j < N; j++) {
			int x2 = cows[j].x, y2 = cows[j].y;

			if (y1 < y2) {
				toignr[i][j] = dp[x2][y2] - 2;
				if (x1 > 0) toignr[i][j] -= dp[x1 - 1][y2];
				if (y1 > 0) toignr[i][j] -= dp[x2][y1 - 1];
				if (x1 > 0 && y1 > 0) toignr[i][j] += dp[x1 - 1][y1 - 1];
			}
			else {
				toignr[i][j] = dp[x2][y1] - 2;
				if (x1 > 0) toignr[i][j] -= dp[x1 - 1][y1];
				if (y2 > 0) toignr[i][j] -= dp[x2][y2 - 1];
				if (x1 > 0 && x2 > 0) toignr[i][j] += dp[x1][y2];
			}
		}
	}

	ll total = 0;
	for (int i = 0; i < N; i++) {
		ll above = 0;
		ll below = 0;
		for (int j = i + 1; j < N; j++) {
			if (cows[j].y < cows[i].y) {
				below++;
				total += (above + 1) * (below - toignr[i][j]);
			}
			else {
				above++;
				total += (below + 1) * (above - toignr[i][j]);
			}
		}
	}
	cout << total + N + 1 << '\n';
}