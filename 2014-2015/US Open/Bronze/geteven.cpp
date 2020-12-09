#include <iostream>
#include <fstream>

using namespace std;

int N;
long long nums[7][3];

long long li(char l) {
	switch (l) {
	case 'B':
		return 0;
	case 'E':
		return 1;
	case 'S':
		return 2;
	case 'I':
		return 3;
	case 'G':
		return 4;
	case 'O':
		return 5;
	case 'M':
		return 6;
	}
}

int solve(int b, int e, int s, int i, int g, int o, int m) {
	int val = (b + e + s + s + i + e) * (g + o + e + s) * (m + o + o);
	return 1 - (val % 2);
}

int main() {
	ifstream fin("geteven.in");
	ofstream fout("geteven.out");

	fin >> N;
	for (int i = 0; i < N; i++) {
		char l;
		int num;
		fin >> l >> num;
		int ind = li(l);
		int eo = num % 2;
		if (eo < 0) eo = -eo;
		nums[ind][eo]++;
		nums[ind][2]++;
	}

	long long total = 0;
	for (int b = 0; b < 2; b++) {
		long long bl = nums[0][b];
		for (int e = 0; e < 2; e++) {
			long long el = nums[1][e];
			for (int s = 0; s < 2; s++) {
				long long sl = nums[2][s];
				for (int i = 0; i < 2; i++) {
					long long il = nums[3][i];
					for (int g = 0; g < 2; g++) {
						long long gl = nums[4][g];
						for (int o = 0; o < 2; o++) {
							long long ol = nums[5][o];
							for (int m = 0; m < 2; m++) {
								long long ml = nums[6][m];
								total += solve(b, e, s, i, g, o, m) * bl * el * sl * il * gl * ol * ml;
							}
						}
					}
				}
			}
		}
	}

	fout << total << '\n';
}