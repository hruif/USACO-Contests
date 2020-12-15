#include <iostream>
#include <fstream>

using namespace std;

int N;
int cows[50000];
int mods[50000];
int mm[7][2];

int main() {
	ifstream fin("div7.in");
	ofstream fout("div7.out");
	
	fin >> N;
	for (int i = 0; i < N; i++) {
		fin >> cows[i];
	}
	
	int sum = 0;
	for (int i = 0; i < N; i++) {
		sum += cows[i];
		sum %= 7;
		mods[i] = sum;
	}

	for (int i = 0; i < 7; i++) {
		mm[i][0] = -1;
	}
	for (int i = 0; i < N; i++) {
		int mod = mods[i];
		if (mm[mod][0] == -1) mm[mod][0] = i;
		mm[mod][1] = i;
	}

	int maxg = 0;
	for (int i = 0; i < 7; i++) {
		int g = mm[i][1] - mm[i][0];
		if (maxg < g) maxg = g;
	}

	fout << maxg << '\n';
}