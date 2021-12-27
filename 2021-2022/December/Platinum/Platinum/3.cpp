#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
using ll = long long;

const ll MOD = 1e9 + 7;

int N, x;

ll fast_pow(ll b, ll e) {
	if (e == 0) return 1;
	ll val = fast_pow(b, e / 2);
	val *= val;
	val %= MOD;
	if (e % 2) val *= b;
	return val % MOD;
}

void mod_mult(ll& a, ll b) {
	a %= MOD;
	b %= MOD;
	a *= b;
	a %= MOD;
}

int main() {
	cin >> N >> x;
	ll num = 1, den = 1;
	ll total_perm = 1;
	for (int i = 1; i <= N; i++) {
		total_perm *= i;
		total_perm %= MOD;
	}
	ll ans = fast_pow(2, MOD - 2) % MOD;
	for (int i = x + 2; i <= N; i++) {
		mod_mult(den, 2);
		ll tden = den, tnum = 1;
		ll td = i - x + 1, tn = i - x - 1;
		for (int j = x; j > 0; j--) {
			mod_mult(tden, td++);
			ans += tnum * fast_pow(tden, MOD - 2);
			ans %= MOD;
			mod_mult(tnum, tn++);
		}
	}
	cout << ans * total_perm % MOD << '\n';
}