#include <iostream>
#include <fstream>
#include <vector>

#define ll long long

using namespace std;

int Q;
vector<ll> kps;

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
		ll cnt = 0;
		int p = 0;
		while (d >= 0 && kps[p] <= max(x, y)) {

		}
	}
}