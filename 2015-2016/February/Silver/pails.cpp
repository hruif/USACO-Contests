#include <iostream>
#include <fstream>
#include <algorithm>
#include <string.h>

using namespace std;

int X, Y, K, M;
int ans = 200;
int ks[105][105];

void updans(int x, int y) {
	ans = min(ans, abs(M - (x + y)));
}

void tryops(int x, int y, int k) {
	if (k < 0) return;
	if (ks[x][y] >= k) return;
	ks[x][y] = k;

	updans(x, y);
	tryops(0, y, k - 1);
	tryops(x, 0, k - 1);
	tryops(x, Y, k - 1);
	tryops(X, y, k - 1);
	int ytox = min(X - x, y);
	tryops(x + ytox, y - ytox, k - 1);
	int xtoy = min(Y - y, x);
	tryops(x - xtoy, y + xtoy, k - 1);
}

int main() {
	ifstream fin("pails.in");
	ofstream fout("pails.out");

	fin >> X >> Y >> K >> M;
	memset(ks, -1, sizeof(ks));
	tryops(0, 0, K);

	fout << ans << '\n';
}