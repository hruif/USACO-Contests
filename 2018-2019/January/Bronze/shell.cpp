#include <iostream>
#include <fstream>

using namespace std;

int N;
int pos[4];
int guessed[4];

int main() {
	ifstream fin("shell.in");
	ofstream fout("shell.out");

	for (int i = 1; i <= 3; i++) {
		pos[i] = i;
	}

	fin >> N;
	for (int i = 0; i < N; i++) {
		int s1, s2, g;
		fin >> s1 >> s2 >> g;
		int p1 = pos[s1];
		int p2 = pos[s2];
		pos[s1] = p2;
		pos[s2] = p1;
		guessed[pos[g]]++;
	}

	int maxguess = 0;
	for (int i = 1; i <= 3; i++) {
		if (guessed[i] > maxguess) maxguess = guessed[i];
	}

	fout << maxguess;
}