#include <iostream>
#include <fstream>
#include <algorithm>
#include <string.h>

#define ll long long

using namespace std;

int n, k;
ll dists[105][105];
int r[100];

int main() {
	ifstream fin("cbarn2.in");
	ofstream fout("cbarn2.out");
	 
	fin >> n >> k;
	for (int i = 0; i < n; i++) fin >> r[i];


	ll result = 1000000000;
	for (int c = 0; c < n; c++) { // cycle through
		memset(dists, 0x3F, sizeof(dists));
		dists[0][n] = 0;

		for (int l = 1; l <= k; l++) {
			for (int i = 0; i < n; i++) {
				ll val = 0;
				for (int j = i; j < n; j++) {
					val += r[j] * (j - i);
					dists[l][i] = min(dists[l][i], val + dists[l - 1][j + 1]);
				}
			}
		}
		result = min(result, dists[k][0]);
		rotate(r, r + 1, r + n);
	}
	fout << result << '\n';
}