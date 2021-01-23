#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <set>
#include <string.h>

using namespace std;

int N;
int in1[50000];
int field[100000];
vector<int> st;

void updst(int k, int x) {
	int sn = st.size() / 2;
	k += sn;
	st[k] = x;
	for (k /= 2; k >= 1; k /= 2) {
		st[k] = st[k * 2] + st[k * 2 + 1];
	}
}

int finds(int a, int b) {
	int sn = st.size() / 2;
	a += sn, b += sn;
	int s = 0;
	while (a <= b) {
		if (a % 2 == 1) s += st[a++];
		if (b % 2 == 0) s += st[b--];
		a /= 2, b /= 2;
	}
	return s;
}

void setst(int n) {
	int sn = 1;
	while (sn < n) sn *= 2;
	sn *= 2;
	st.resize(sn, 0);
}

int main() {
	memset(in1, -1, sizeof(in1));

	ifstream fin("circlecross.in");
	ofstream fout("circlecross.out");

	fin >> N;
	for (int i = 0; i < 2 * N; i++) {
		fin >> field[i];
		field[i]--;
	}
	
	setst(2 * N);
	int pairs = 0;
	for (int i = 0; i < 2 * N; i++) {
		int val = field[i];
		if (in1[val] != -1) {
			updst(i, 0);
			updst(in1[val], 0);
			pairs += finds(in1[val], i);
		}
		else {
			in1[val] = i;
			updst(i, 1);
		}
	}

	fout << pairs << '\n';
}