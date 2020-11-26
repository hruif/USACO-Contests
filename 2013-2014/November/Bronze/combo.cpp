#include <iostream>
#include <fstream>
#include <algorithm>
#include <math.h>
#include <string.h>
#include <unordered_set>

using namespace std;

int N;
int fj[3];
int m[3]; 
int found[250][3];
unordered_set<int> combos;

int round(int a) {
	if (a < 0) {
		a += N;
	}
	return a % N;
}

int main() {
	ifstream fin("combo.in");
	fin >> N;
	fin >> fj[0] >> fj[1] >> fj[2];
	fj[0]--;
	fj[1]--;
	fj[2]--;
	fin >> m[0] >> m[1] >> m[2];
	m[0]--;
	m[1]--;
	m[2]--;
	int count = 0;
	for (int i = -2; i <= 2; i++) {
		int f1 = round(fj[0] + i);
		int m1 = round(m[0] + i);
		f1 *= 50 * 50;
		m1 *= 50 * 50;
		for (int j = -2; j <= 2; j++) {
			int f2 = round(fj[1] + j);
			int m2 = round(m[1] + j);
			f2 *= 50;
			m2 *= 50;
			for (int k = -2; k <= 2; k++) {
				int f3 = round(fj[2] + k);
				int m3 = round(m[2] + k);
				int ftot = f1 + f2 + f3;
				int mtot = m1 + m2 + m3;
				if (combos.find(ftot) == combos.end()) {
					combos.insert(ftot);
				}
				if (combos.find(mtot) == combos.end()) {
					combos.insert(mtot);
				}
			}
		}
	}

	ofstream fout("combo.out");
	fout << combos.size() << '\n';
}