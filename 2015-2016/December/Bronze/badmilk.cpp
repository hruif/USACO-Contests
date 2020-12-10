#include <iostream>
#include <fstream>

using namespace std;

int N, M, D, S;
int st[50];
int Ds[1000][3];
bool milks[50][50];
bool badmilks[50];

int main() {
	for (int i = 0; i < 50; i++) {
		st[i] = 101;
	}

	ifstream fin("badmilk.in");
	ofstream fout("badmilk.out");

	fin >> N >> M >> D >> S;
	for (int i = 0; i < D; i++) {
		fin >> Ds[i][0] >> Ds[i][1] >> Ds[i][2];
	}
	for (int i = 0; i < S; i++) {
		int p, t;
		fin >> p >> t;
		p -= 1;
		st[p] = t;
	}

	for (int i = 0; i < D; i++) {
		int p = Ds[i][0] - 1;
		int m = Ds[i][1] - 1;
		int t = Ds[i][2];
		if (t < st[p]) milks[p][m] = true;
	}

	for (int i = 0; i < M; i++) {
		bool bad = true;
		for (int j = 0; j < N; j++) {
			if (st[j] < 101) {
				bad = bad && milks[j][i];
			}
		}
		badmilks[i] = bad;
	}
	int doses = 0;
	for (int i = 0; i < N; i++) {
		bool drank = false;
		for (int j = 0; j < M; j++) {
			if (milks[i][j] && badmilks[j]) drank = true;
		}
		if (drank) doses++;
	}

	fout << doses << '\n';
}