#include <iostream>
#include <fstream>
#include <algorithm>
#include <iomanip>

using namespace std;

int N;
int x[50000];
int dists[50000];
int premax[50000];
int sufmax[50000];

int lrs[50000];
int rrs[50000];

int main() {
	ifstream fin("angry.in");
	ofstream fout("angry.out");

	fin >> N;
	for (int i = 0; i < N; i++) fin >> x[i];
	sort(x, x + N);
	for (int i = 1; i < N; i++) dists[i] = x[i] - x[i - 1];

	int r = 0;
	int xpos = x[0];
	lrs[0] = 0;
	int p = 1;
	while (p < N) {
		while (p < N && xpos + r >= x[p]) {
			lrs[p] = r;
			p++;
		}
		r++;
		xpos = x[p - 1];
	}
	r = 0, xpos = x[N - 1], rrs[N - 1] = 0, p = N - 2;

	while (p >= 0) {
		while (p >= 0 && xpos - r <= x[p]) {
			rrs[p] = r;
			p--;
		}
		r++;
		xpos = x[p + 1];
	}

	p = 0;
	while (p < N && rrs[p] > lrs[p]) {
		p++;
	}
	int l = p - 1, ri = p + 1;
	while (l >= 0 && lrs[l] == lrs[p - 1]) l--;
	while (p < N && rrs[ri] == rrs[p]) ri++;
	double distR = x[p] - x[p - 1];
	distR /= 2;
	double ans = max(distR, max((double)(lrs[p - 1] + 1), (double)(rrs[p] + 1)));
	if (l >= 0) {
		distR = x[p] - x[l];
		distR /= 2;
		ans = min(ans, max(distR, max((double)(lrs[p - 1]), (double)(rrs[p] + 1))));
	}
	if (r < N) {
		distR = x[ri] - x[p];
		distR /= 2;
		ans = min(ans, max(distR, max((double)(lrs[p - 1] + 1), (double)(rrs[p]))));
	}
	if (l >= 0) {
		distR = x[ri] - x[l];
		distR /= 2;
		ans = min(ans, max(distR, max((double)(lrs[p - 1]), (double)(rrs[p]))));
	}
	double non = ans * 10;
	int val = ans;
	non = (int)(non) % 10;
	char d = non + '0';
	fout << val  << '.' << d << '\n';
}