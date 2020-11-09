/*
ID: ruifanl1
TASK: stacking
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

int N, K;
int starts[1000000];
int endings[1000000];
int stacks[1000000];

int main() {
	ifstream fin("stacking.in");
	fin >> N >> K;
	for (int i = 0; i < K; i++) {
		int l, r;
		fin >> l >> r;
		starts[l - 1]++;
		endings[r - 1]++;
	}

	int s = 0;
	for (int i = 0; i < N; i++) {
		s += starts[i];
		stacks[i] = s;
		s -= endings[i];
	}
	sort(stacks, stacks + N);

	ofstream fout("stacking.out");
	fout << stacks[N / 2] << '\n';
}