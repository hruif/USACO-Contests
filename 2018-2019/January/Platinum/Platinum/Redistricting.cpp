#include <iostream>
#include <fstream>
#include <set>

using namespace std;

ifstream fin("redistricting.in");
ofstream fout("redistricting.out");

int N, K;
char cows[300000];
int p[300000], dp[300000];

multiset<int> vals;
multiset<int> ps[300000];
int main() {
	fin >> N >> K;
	for (int i = 0; i < N; i++) fin >> cows[i];
	p[0] = (cows[0] == 'H' ? 1 : -1);
	for (int i = 1; i < N; i++) {
		p[i] = p[i - 1] + (cows[i] == 'H' ? 1 : -1);
	}
	dp[0] = (cows[0] == 'G' ? 1 : 0);
	vals.insert(dp[0]);
	ps[dp[0]].insert(p[0]);
	for (int i = 1; i < N; i++) {
		int mv = *vals.begin();
		if (p[i] - *ps[mv].begin() > 0) dp[i] = mv;
		else dp[i] = mv + 1;

		vals.insert(dp[i]);
		ps[dp[i]].insert(p[i]);
		if (vals.size() > K) {
			int v = dp[i - K];
			ps[v].erase(ps[v].find(p[i - K]));
			vals.erase(vals.find(v));
		}
	}
	fout << dp[N - 1] << '\n';
}