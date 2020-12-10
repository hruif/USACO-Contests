#include <iostream>
#include <fstream>

using namespace std;

int N, M;
int road[100];
int bes[100];

int main() {
	ifstream fin("speeding.in");
	ofstream fout("speeding.out");

	fin >> N >> M;
	int dist = 0;
	for (int i = 0; i < N; i++) {
		int len, lim;
		fin >> len >> lim;
		for (int j = 0; j < len; j++) {
			road[dist++] = lim;
		}
	}
	dist = 0;
	for (int i = 0; i < M; i++) {
		int len, lim;
		fin >> len >> lim;
		for (int j = 0; j < len; j++) {
			bes[dist++] = lim;
		}
	}

	int maxover = 0;
	for (int i = 0; i < 100; i++) {
		int over = bes[i] - road[i];
		if (over > maxover) maxover = over;
	}

	fout << maxover << '\n';
}