#include <iostream>
#include <algorithm>

#define ll long long
#define INF 1e18

using namespace std;

int N;
ll cows[50][3];
ll dists[50];

int main() {
	for (int i = 0; i < 50; i++) dists[i] = INF;

	cin >> N;
	for (int i = 0; i < N; i++) {
		char dir;
		cin >> dir >> cows[i][0] >> cows[i][1];
		if (dir == 'N') cows[i][2] = 0;
		else cows[i][2] = 1;
	}

	bool cross = false;
	ll firstim = INF;
	for (int i = 0; i < N; i++) {
		ll x1 = cows[i][0];
		ll y1 = cows[i][1];
		ll dir1 = cows[i][2];
		for (int j = i + 1; j < N; j++) {
			ll x2 = cows[j][0];
			ll y2 = cows[j][1];
			ll dir2 = cows[j][2];

			if (dir1 == dir2) continue;

			if (dir1 == 0) {
				if (y1 < y2 && x2 < x1) {
					cross = true;

					ll dist1 = y2 - y1;
					ll dist2 = x1 - x2;
					if (dist1 == dist2) continue;

					firstim = min(firstim, max(dist1, dist2));
				}
			}
			else {
				if (y2 < y1 && x1 < x2) {
					cross = true;

					ll dist1 = x2 - x1;
					ll dist2 = y1 - y2;
					if (dist1 == dist2) continue;

					firstim = min(firstim, max(dist1, dist2));
				}
			}
		}
	}

	while (cross) {
		cross = false;
		for (int i = 0; i < N; i++) {
			ll x1 = cows[i][0];
			ll y1 = cows[i][1];
			ll dir1 = cows[i][2];
			for (int j = i + 1; j < N; j++) {
				ll x2 = cows[j][0];
				ll y2 = cows[j][1];
				ll dir2 = cows[j][2];

				if (dir1 == dir2) continue;

				if (dir1 == 0) {
					if (y1 < y2 && x2 < x1) {
						ll dist1 = y2 - y1;
						ll dist2 = x1 - x2;
						if (dist1 == dist2) continue;

						if (dist1 > dists[i] || dist2 > dists[j]) continue;
						if (max(dist1, dist2) == firstim) {
							if (dist1 == firstim) dists[i] = dist1 - 1;
							else dists[j] = dist2 - 1;
						}
					}
				}
				else {
					if (y2 < y1 && x1 < x2) {
						ll dist1 = x2 - x1;
						ll dist2 = y1 - y2;
						if (dist1 == dist2) continue;

						if (dist1 > dists[i] || dist2 > dists[j]) continue;
						if (max(dist1, dist2) == firstim) {
							if (dist1 == firstim) dists[i] = dist1 - 1;
							else dists[j] = dist2 - 1;
						}
					}
				}
			}
		}

		firstim = INF;
		for (int i = 0; i < N; i++) {
			ll x1 = cows[i][0];
			ll y1 = cows[i][1];
			ll dir1 = cows[i][2];
			for (int j = i + 1; j < N; j++) {
				ll x2 = cows[j][0];
				ll y2 = cows[j][1];
				ll dir2 = cows[j][2];

				if (dir1 == dir2) continue;

				if (dir1 == 0) {
					if (y1 < y2 && x2 < x1) {

						ll dist1 = y2 - y1;
						ll dist2 = x1 - x2;
						if (dist1 == dist2) continue;

						if (dist1 > dists[i] || dist2 > dists[j]) continue;
						cross = true;
						firstim = min(firstim, max(dist1, dist2));
					}
				}
				else {
					if (y2 < y1 && x1 < x2) {

						ll dist1 = x2 - x1;
						ll dist2 = y1 - y2;
						if (dist1 == dist2) continue;

						if (dist1 > dists[i] || dist2 > dists[j]) continue;
						cross = true;
						firstim = min(firstim, max(dist1, dist2));
					}
				}
			}
		}
	}

	for (int i = 0; i < N; i++) {
		if (dists[i] == INF) cout << "Infinity\n";
		else cout << dists[i] + 1 << '\n';
	}
}