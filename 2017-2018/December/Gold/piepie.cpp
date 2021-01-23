#include <iostream>
#include <fstream>
#include <algorithm>
#include <string.h>
#include <queue>

using namespace std;

struct Pie {
	int a, b, i;
	bool operator<(const Pie p) const {
		return b < p.b;
	}
};

struct Ex {
	int p;
	int i, m;
};

int N, D;
int dp[100000];
Pie pies[2][100000];
queue<Ex> exchanges;
int ans[100000];
bool visited[2][100000];

int main() {
	memset(dp, -1, sizeof(dp));
	memset(ans, -1, sizeof(ans));

	ifstream fin("piepie.in");
	ofstream fout("piepie.out");

	fin >> N >> D;
	for (int i = 0; i < N; i++) {
		fin >> pies[0][i].a >> pies[0][i].b;
		pies[0][i].i = i;
	}
	for (int i = 0; i < N; i++) {
		fin >> pies[1][i].b >> pies[1][i].a;
		pies[1][i].i = i;
	}
	sort(pies[0], pies[0] + N);
	sort(pies[1], pies[1] + N);

	int ep = N - 1;
	for (int i = 0; i < N; i++) {
		Ex p0{ 0, i, 1 };
		Ex p1{ 1, i, 1 };
		if (pies[0][i].b == 0) {
			exchanges.push(p0);
		}
		if (pies[1][i].b == 0) {
			exchanges.push(p1);
		}
	}
	while (!exchanges.empty()) {
		Ex ex = exchanges.front();
		exchanges.pop();
		int p = ex.p, pi = ex.i, m = ex.m;
		int a = pies[p][pi].a, b = pies[p][pi].b;
		if (p == 0) {
			int i = pies[0][pi].i;
			if (ans[i] == -1) {
				ans[i] = m;
				auto pp = lower_bound(pies[1], pies[1] + N, Pie{ 0, a - D });
				while (pp != pies[1] + N && pp->b <= a) {
					Ex next{ 1, pp - pies[1], m + 1 };
					exchanges.push(next);
					pp++;
				}
			}
		}
		else {
			auto pp = lower_bound(pies[0], pies[0] + N, Pie{ 0, a - D });
			while (pp != pies[0] + N && pp->b <= a) {
				Ex next{ 0, pp - pies[0], m + 1 };
				exchanges.push(next);
				pp++;
			}
		}
	}
	for (int i = 0; i < N; i++) {
		fout << ans[i] << '\n';
	}
}