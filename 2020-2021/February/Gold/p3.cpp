#include <iostream>
#include <fstream>
#include <vector>
#include <string.h>

#define ll long long

using namespace std;

int Q;
vector<ll> kps;

vector<int> tob3(ll v) {
	vector<int> b3(kps.size(), 0);
	ll p = 1;
	for (int i = 1; i < kps.size(); i++) p *= 3;
	for (int i = b3.size() - 1; i >= 0; i--) {
		while (v >= p) {
			v -= p;
			b3[i]++;
		}
		p /= 3;
	}
	return b3;
}

int main() {
	ll kp = 1;
	while (kp <= 2000000000000000000LL) {
		kps.push_back(kp);
		kp *= 3;
	}
	kps.push_back(kp);

	cin >> Q;
	while (Q--) {
		ll d, x, y;
		cin >> d >> x >> y;
		vector<int> db3 = tob3(d), xb3 = tob3(x), yb3 = tob3(y);
		ll dp[41][2][2][3];
		memset(dp, 0, sizeof(dp));
		dp[0][0][0][0] = 1;
		for (int i = 0; i < kps.size(); i++) {
			int xv = xb3[i], yv = yb3[i];
			for (int incx = 0; incx < 2; incx++) {
				for (int incy = 0; incy < 2; incy++) {
					for (int inc = 0; inc < 3; inc++) {
						for (int piv = 0; piv < 3; piv++) {
							int nxv = xv + incx + inc, nyv = yv + incy + inc;
							int toincx = nxv / 3, toincy = nyv / 3;
							nxv %= 3; nyv %= 3;
							int iv = piv;
							if (inc < db3[i]) iv = 0;
							if (inc > db3[i]) iv = 2;
							if (nxv % 2 == nyv % 2) {
								dp[i + 1][toincx][toincy][iv] += dp[i][incx][incy][piv];
							}
						}
					}
				}
			}
		}
		cout << dp[kps.size()][0][0][0] + dp[kps.size()][0][0][1] << '\n';
	}
}