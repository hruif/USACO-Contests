#include <iostream>
#include <fstream>
#include <utility>
#include <vector>
#include <algorithm>

using namespace std;

using ll = long long;
using pii = pair<int, int>;

#define MOD (ll)(1e9 + 7)


struct Tri {
	int a, b, c;
	Tri() {}
	Tri(int a, int b, int c) {
		this->a = a;
		this->b = b;
		this->c = c;
	}
};

int N;
int x[40], y[40];
int dp[40][40][40][41];

ll pow(ll b, ll e) {
	if (e == 0) return b;
	ll val = pow(b, e / 2);
	val *= val;
	val %= 1000000007;
	if (e % 2) val *= b;
	return val % 1000000007;
}

ll cross(pii a, pii b, pii c) {
	b.first -= a.first; b.second -= a.second;
	c.first -= a.first; c.second -= a.second;
	return b.first * c.second - b.second * c.first;
}

ll area(pii a, pii b, pii c) {
	return abs(cross(a, b, c));
}

bool inside(pii a, pii b, pii c, pii p) {
	ll sum = 0;
	sum += area(a, b, p);
	sum += area(a, p, c);
	sum += area(p, b, c);
	return sum == area(a, b, c);
}

int main() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			for (int k = 0; k < N; k++) {
				for (int l = 0; l < N; l++) {
					dp[i][j][k][l] = 0;
				}
			}
		}
	}

	cin >> N;

	for (int i = 0; i < N; i++) {
		cin >> x[i] >> y[i];
	}
	
	ll ans = 0;
	vector<Tri> triangles;
	for (int i = 0; i < N; i++) {
		for (int j = i + 1; j < N; j++) {
			if (j == i) continue;
			for (int k = j + 1; k < N; k++) {
				if (k == i || k == j) continue;
				triangles.push_back(Tri(i, j, k));
			}
		}
	}
	sort(triangles.begin(), triangles.end(), [&](Tri a, Tri b) {
		return area({ x[a.a], y[a.a] }, { x[a.b], y[a.b] }, { x[a.c], y[a.c] }) <
			area({ x[b.a], y[b.a] }, { x[b.b], y[b.b] }, { x[b.c], y[b.c] });
		});

	for (auto& t : triangles) {
		int i = t.a, j = t.b, k = t.c;
		pii a = { x[i], y[i] }, b = { x[j], y[j] }, c = { x[k], y[k] };

		int intri = 0;
		vector<Tri> nex;
		for (int l = 0; l < N; l++) {
			if (l == i || l == j || l == k) continue;
			pii p = { x[l], y[l] };

			if (inside(a, b, c, p)) {
				intri++;
			}
			else {
				int arr[3] = { i, j, k };
				if (inside(a, b, p, c)) {
					arr[2] = l;
					sort(arr, arr + 3);
					nex.push_back(Tri(arr[0], arr[1], arr[2]));
				}
				if (inside(a, p, c, b)) {
					arr[1] = l;
					sort(arr, arr + 3);
					nex.push_back(Tri(arr[0], arr[1], arr[2]));
				}
				if (inside(p, b, c, a)) {
					arr[0] = l;
					sort(arr, arr + 3);
					nex.push_back(Tri(arr[0], arr[1], arr[2]));
				}
			}
		}

		dp[i][j][k][0] = 1;
		for (int m = 0; m <= intri; m++) {
			ll v = dp[i][j][k][m];
			if (m < intri) {
				dp[i][j][k][m + 1] += (intri - m) * v % MOD;
				dp[i][j][k][m + 1] %= MOD;
			}
			for (Tri u : nex) {
				dp[u.a][u.b][u.c][m + 1] += v;
				dp[u.a][u.b][u.c][m + 1] %= MOD;
			}
		}
		if (intri == N - 3) {
			ans += dp[i][j][k][intri];
		}
	}

	/*for (int i = 0; i < N; i++) {
		pii a = { x[i], y[i] };
		for (int j = 0; j < N; j++) {
			if (j == i) continue;
			pii b = { x[j], y[j] };
			for (int k = 0; k < N; k++) {
				if (k == i || k == j) continue;
				pii c = { x[k], y[k] };

				int intri = 0;
				vector<Tri> nex;
				for (int l = 0; l < N; l++) {
					if (l == i || l == j || l == k) continue;
					pii p = { x[l], y[l] };

					if (inside(a, b, c, p)) {
						intri++;
					}
					else {
						if (inside(a, b, p, c)) {
							nex.push_back(Tri(i, j, l));
						} 
						if (inside(a, p, c, b)) {
							nex.push_back(Tri(i, l, k));
						}
						if (inside(p, b, c, a)) {
							nex.push_back(Tri(l, j, k));
						}
					}
				}

				dp[i][j][k][0] = 1;
				for (int m = 0; m < intri; m++) {
					ll v = dp[i][j][k][m];
					if (i < intri) {
						dp[i][j][k][m + 1] = (intri - 1) * v % MOD;
					}
					for (Tri u : nex) {
						dp[u.a][u.b][u.c][m + 1] = v;
					}
				}
				if (intri == N - 3) {
					ans += dp[i][j][k][intri];
				}
			}
		}
	}*/
	cout << ans * 6 % MOD << '\n';
}