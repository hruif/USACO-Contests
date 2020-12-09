#include <iostream>
#include <fstream>

using namespace std;

int N;
int spds[100000];

int main() {
	ifstream fin("cowjog.in");
	ofstream fout("cowjog.out");

	fin >> N;
	for (int i = 0; i < N; i++) {
		int tmp;
		fin >> tmp >> spds[i];
	}

	int spd = spds[N - 1];
	int groups = 1;
	for (int i = N - 2; i >= 0; i--) {
		if (spds[i] <= spd) {
			spd = spds[i];
			groups++;
		}
	}
	
	fout << groups << '\n';
}