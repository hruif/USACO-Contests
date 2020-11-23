#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <string.h>
#include <algorithm>
#include <math.h>
#include <unordered_map>

using namespace std;
using ll = long long;
using vi = vector<int>;
using vll = vector<ll>;
using vc = vector<char>;
using pii = pair<int, int>;
using vpii = vector<pii>;
using umii = unordered_map<int, int>;
using umllll = unordered_map<ll, ll>;

#define FORI(i, a, b, p) for (int i = a; i < b; i += p)
#define FOR(i, a, b) FORI(i, a, b, 1)
#define F0R(i,b) FOR(i, 0, b)
#define RFOR(i, a, b) for (int i = a; i >= b; i--)
#define RF0R(i, a) RFOR(i, a, 0)

#define MOD 998244353

ll N, B;
umllll val;

ll toggleBulbs(ll bulbs) {
	ll b = 1;
	ll tBulbs = 0;
	bool toggle = b & bulbs;
	b <<= 1;
	FOR(i, 1, N) {
		if (toggle) {
			if ((bulbs & b) == 0) {
				tBulbs += b;
			}
			toggle = false;
		}
		else {
			if (bulbs & b) {
				tBulbs += b;
			}
		}
		if (bulbs & b) {
			toggle = true;
		}
		b <<= 1;
	}
	b = 1;
	if (toggle) {
		if ((bulbs & b) == 0) {
			tBulbs += b;
		}
		toggle = false;
	}
	else {
		if (bulbs & b) {
			tBulbs += b;
		}
	}
	return tBulbs;
}

int main() {
	ifstream fin("blink.in");
	fin >> N >> B;
	ll bulbs = 0;
	ll b = 1;
	F0R(i, N) {
		int bulb;
		fin >> bulb;
		if (bulb == 1) {
			bulbs |= b;
		}
		b <<= 1;
	}
	ll newBulbs = toggleBulbs(bulbs);
	ll moves = 1;
	while (val.find(newBulbs) == val.end() && moves < B) {
		val[newBulbs] = moves;
		newBulbs = toggleBulbs(newBulbs);
		moves++;
	}
	if (moves < B) {
		B -= val[newBulbs];
		B %= moves - val[newBulbs];
		moves = 0;
		while (moves < B) {
			newBulbs = toggleBulbs(newBulbs);
			moves++;
		}
	}
	ofstream cout("blink.out");
	b = 1;
	for (int i = 0; i < N; i++) {
		if (newBulbs & b) {
			cout << "1\n";
		}
		else {
			cout << "0\n";
		}
		b <<= 1;
	}
}