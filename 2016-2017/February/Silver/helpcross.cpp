#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

struct cowt {
	int A;
	int B;
	bool operator<(const cowt a) const {
		return B < a.B;
	}
};

int C, N;
int chicks[20000];
cowt cows[20000];

int main() {
	ifstream fin("helpcross.in");
	ofstream fout("helpcross.out");

	fin >> C >> N;
	for (int i = 0; i < C; i++) {
		fin >> chicks[i];
	}
	for (int i = 0; i < N; i++) {
		fin >> cows[i].A >> cows[i].B;
	}
	sort(chicks, chicks + C);
	sort(cows, cows + N);
	
	int p = 0;
	for (int i = 0; i < C; i++) {
		while (
	}
}