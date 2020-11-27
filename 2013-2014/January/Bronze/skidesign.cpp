#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

int N;
int hills[1000];

int main() {
	ifstream fin("skidesign.in");
	fin >> N;
	for (int i = 0; i < N; i++) {
		fin >> hills[i];
	}
	sort(hills, hills + N);
	int min = -1;
	for (int i = 1; i <= 100; i++) {
		int total = 0;
		for (int j = 0; j < N; j++) {
			if (hills[j] < i) {
				total += (i - hills[j]) * (i - hills[j]);
			}
			if (hills[j] > i + 17) {
				int max = i + 17;
				total += (max - hills[j]) * (max - hills[j]);
			}
		}
		if (total < min || min == -1) {
			min = total;
		}
	}
	ofstream fout("skidesign.out");
	fout << min << '\n';
}