#include <iostream>
#include <fstream>

using namespace std;

int n;
int c[1000];
int moves[1000];

int main() {
	ifstream fin("cbarn.in");
	ofstream fout("cbarn.out");

	fin >> n;
	for (int i = 0; i < n; i++) {
		fin >> c[i];
	}
	int cnt = 0;
	int p = 0;
	while (cnt < n) {
		if (p == n) p = 0;
		if (c[p] > 0 && c[(p + 1) % n] == 0) {
			cnt = 0;
			c[p]--;
			c[(p + 1) % n]++;
			moves[(p + 1) % n] = moves[p] + 1;
			moves[p] = 0;
		}
		else cnt++;
		p++;
	}

	int energy = 0;
	for (int i = 0; i < n; i++) {
		energy += moves[i] * moves[i];
	}
	fout << energy << '\n';
}