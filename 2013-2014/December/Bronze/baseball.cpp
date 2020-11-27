#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

int N;
int cows[1000];

int main() {
	ifstream fin("baseball.in");
	fin >> N;
	for (int i = 0; i < N; i++) {
		fin >> cows[i];
	}
	sort(cows, cows + N);
	int total = 0;
	for (int i = 0; i < N - 2; i++) {
		for (int j = i + 1; j < N - 1; j++) {
			int dist = cows[j] - cows[i];
			for (int k = j + 1; k < N; k++) {
				int dist2 = cows[k] - cows[j];
				if (dist2 < dist || dist * 2 < dist2) {
					continue;
				}
				total++;
			}
		}
	}
	ofstream fout("baseball.out");
	fout << total << '\n';
}