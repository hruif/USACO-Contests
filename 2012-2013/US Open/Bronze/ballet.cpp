#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <string.h>
#include <algorithm>
#include <math.h>

using namespace std;
using ll = long long;
using vi = vector<int>;
using vll = vector<ll>;
using vc = vector<char>;
using pii = pair<int, int>;
using vpii = vector<pii>;

#define f first
#define s second

#define pb push_back

#define FORI(i, a, b, p) for (int i = a; i < b; i += p)
#define FOR(i, a, b) FORI(i, a, b, 1)
#define F0R(i,b) FOR(i, 0, b)
#define RFOR(i, a, b) for (int i = a; i >= b; i--)
#define RF0R(i, a) RFOR(i, a, 0)

#define MOD 998244353

int N;
int bdir = 0; // Bessie's direction
pii FL(0, 1), FR(1, 1), RL(0, 0), RR(1, 0);

void rotate(pii& leg) {
	int xdif = leg.f;
	int ydif = leg.s;

	int absx = FL.f - xdif;
	int absy = FL.s - ydif;
	FL.f = absy + xdif;
	FL.s = -absx + ydif;

	absx = FR.f - xdif;
	absy = FR.s - ydif;
	FR.f = absy + xdif;
	FR.s = -absx + ydif;

	absx = RL.f - xdif;
	absy = RL.s - ydif;
	RL.f = absy + xdif;
	RL.s = -absx + ydif;

	absx = RR.f - xdif;
	absy = RR.s - ydif;
	RR.f = absy + xdif;
	RR.s = -absx + ydif;
	bdir++;
	bdir %= 4;
}

void movel(pii& leg, int dir) {
	dir += bdir;
	dir %= 4;
	switch (dir) {
	case 0:
		leg.s++;
		break;
	case 1:
		leg.f++;
		break;
	case 2:
		leg.s--;
		break;
	case 3:
		leg.f--;
		break;
	}
}

bool ss(pii& a, pii& b) { // same square
	return a.f == b.f && a.s == b.s;
}

bool trip() {
	if (ss(FL, FR) || ss(FL, RL) || ss(FL, RR)
		|| ss(FR, RL) || ss(FR, RR) || ss(RL, RR)) {
		return true;
	}
	return false;
}

int main() {
	ifstream fin("ballet.in");
	fin >> N;
	int minX = 0;
	int maxX = 1;
	int minY = 0;
	int maxY = 1;
	bool tripped = false;
	F0R(i, N) {
		string leg;
		char fb, lr;
		char dir;
		fin >> fb >> lr >> dir;
		leg.pb(fb);
		leg.pb(lr);
		if (dir == 'P') {
			if (leg == "FL") {
				rotate(FL);
			}
			else if (leg == "FR") {
				rotate(FR);
			}
			else if (leg == "RL") {
				rotate(RL);
			}
			else {
				rotate(RR);
			}
		}
		else {
			if (dir == 'F') {
				dir = 0;
			}
			else if (dir == 'R') {
				dir = 1;
			}
			else if (dir == 'B') {
				dir = 2;
			}
			else {
				dir = 3;
			}
			if (leg == "FL") {
				movel(FL, dir);
			}
			else if (leg == "FR") {
				movel(FR, dir);
			}
			else if (leg == "RL") {
				movel(RL, dir);
			}
			else {
				movel(RR, dir);
			}
		}
		minX = min(minX, min(min(FL.f, FR.f), min(RL.f, RR.f)));
		maxX = max(maxX, max(max(FL.f, FR.f), max(RL.f, RR.f)));
		minY = min(minY, min(min(FL.s, FR.s), min(RL.s, RR.s)));
		maxY = max(maxY, max(max(FL.s, FR.s), max(RL.s, RR.s)));
		if (trip()) {
			tripped = true;
		}
	}
	ofstream fout("ballet.out");
	if (tripped) {
		fout << "-1\n";
	}
	else {
		int w = maxX - minX + 1;
		int h = maxY - minY + 1;
		fout << w * h << '\n';
	}
}