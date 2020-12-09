#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

struct hb {
	int s;
	int x;
	bool operator<(const hb a) const {
		return x < a.x;
	}
};

int N;
hb haybales[4000];

int main() {
	ifstream fin("trapped.in");
	ofstream fout("trapped.out");

	fin >> N;
	for (int i = 0; i < N; i++) {
		fin >> haybales[i].s >> haybales[i].x;
	}
	sort(haybales, haybales + N);

	int mindist = -1;
	for (int i = 1; i < N; i++) {
		if (min(haybales[i].s, haybales[i - 1].s) >= haybales[i].x - haybales[i - 1].x) {
			if (haybales[i].x - haybales[i - 1].x < mindist || mindist == -1) {
				mindist = haybales[i].x - haybales[i - 1].x;
			}
		}
	}

	fout << mindist << '\n';
}