#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>

#define MOD 1000000007
#define ll long long

using namespace std;

int N, M, K;
ll schemes[26];
ll lens[5001];
ll classes[5001];
ll words[5001][5001];
ll endclass[5001];

ll exponentiate(ll base, ll ex) {
	if (ex == 0) return 1;
	if (ex == 1) return base % MOD;
	ll val = exponentiate(base, ex / 2);
	if (val < 0) cin >> val;
	val *= val;
	val %= MOD;
	if (ex % 2 == 1) val *= base;
	return val % MOD;
}

ll built[5001];
ll waysfrom[5001];
ll findfroms(int lastsyls, int len) {
	if (len == 0) return 1;

	if (built[len] < 5001) return waysfrom[len];
	built[len] = lastsyls;

	ll ways = 0;
	for (int i = 1; i < K; i++) {
		if (len - i >= 0) ways += (findfroms(i, len - i) * lens[i]) % MOD;
		else break;
		ways %= MOD;
	}
	waysfrom[len] = ways;
	return ways;
}

void findendclass(int cl) {
	for (int i = 0; i < K; i++) {
		endclass[cl] += (words[K - i][cl] * waysfrom[i]) % MOD;
	}
	endclass[cl] %= MOD;
}

int main() {
	ifstream fin("poetry.in");
	ofstream fout("poetry.out");

	fin >> N >> M >> K;
	for (int i = 0; i < N; i++) {
		int s, c;
		fin >> s >> c;
		lens[s]++;
		classes[c]++;
		words[s][c]++;
	}
	for (int i = 0; i < M; i++) {
		char sch;
		fin >> sch;
		schemes[sch - 'A']++;
	}

	for (int i = 0; i < 5001; i++) {
		built[i] = 5001;
	}
	for (int i = 0; i < K; i++) {
		findfroms(0, i);
	}
	for (int i = 1; i <= N; i++) {
		findendclass(i);
	}

	ll total = 1;
	for (int i = 0; i < 26; i++) {
		if (schemes[i] == 0) continue;
		ll sum = 0;
		for (int j = 1; j <= N; j++) {
			ll val = exponentiate(endclass[j], schemes[i]);
			if (val < 0) cin >> val;
			sum += val;
			sum %= MOD;
		}
		total *= sum;
		total %= MOD;
	}

	fout << total << '\n';
}