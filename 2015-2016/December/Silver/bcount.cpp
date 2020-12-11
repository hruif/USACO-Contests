#include <iostream>
#include <fstream>

using namespace std;

int h[100005], g[100005], j[100005];
int qs[100005][3];

int main() {
	ifstream fin("bcount.in");
	ofstream fout("bcount.out");

	int N, Q;
	fin >> N >> Q;
	int hs = 0, gs = 0, js = 0;
	for (int i = 0; i < N; i++) {
		int c;
		fin >> c;
		switch (c) {
		case 1:
			hs++;
			break;
		case 2:
			gs++;
			break;
		case 3:
			js++;
			break;
		}
		h[i] = hs;
		g[i] = gs;
		j[i] = js;
	}
	for (int i = 0; i < Q; i++) {
		int a, b;
		fin >> a >> b;
		a--, b--;
		if (a == 0) {
			qs[i][0] = h[b];
			qs[i][1] = g[b];
			qs[i][2] = j[b];
		}
		else {
			qs[i][0] = h[b] - h[a - 1];
			qs[i][1] = g[b] - g[a - 1];
			qs[i][2] = j[b] - j[a - 1];
		}
	}

	for (int i = 0; i < Q; i++) {
		fout << qs[i][0] << ' ' << qs[i][1] << ' ' << qs[i][2] << '\n';
	}
}