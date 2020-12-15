#include <iostream>
#include <fstream>
#include <unordered_set>

#define ll long long

using namespace std;

int N;
unordered_set<ll> ps;
unordered_set<ll> vs;

ll lettodir(char let) {
	switch (let) {
	case 'N':
		return 0;
	case 'E':
		return 1;
	case 'S':
		return 2;
	case 'W':
		return 3;
	}
}

int main() {
	ifstream fin("gates.in");
	ofstream fout("gates.out");

	fin >> N;
	ll x = 1000, y = 1000;
	int cs = 0;
	for (int i = 0; i < N; i++) {
		char let;
		fin >> let;
		ll dir = lettodir(let);
		ll p = x * 10000 + y;
		ll val = x * 10000 * 10000 + y * 10000 + ((dir + 2) % 4);
		ps.insert(p);
		vs.insert(val);

		if (let == 'N') y++;
		else if (let == 'E') x++;
		else if (let == 'S') y--;
		else if (let == 'W') x--;

		val = x * 10000 * 10000 + y * 10000 + dir;
		p = x * 10000 + y;
		if (ps.find(p) != ps.end()) {
			if (vs.find(val) == vs.end()) {
				cs++;
			}
		}
		vs.insert(val);
	}
	fout << cs << '\n';
}