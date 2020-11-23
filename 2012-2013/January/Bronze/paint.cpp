#include <iostream>
#include <fstream>
#include <vector>
#include <utility>

using namespace std;

int N;
vector<pair<int, int>> segs;

int main() {
	ifstream fin("input.in");
	fin >> N;
	int x = 0, segPos = 0;
	int l = 0, r = 0;
	for (int i = 0; i < N; i++) {
		int units;
		char dir;
		fin >> units >> dir;
		if (dir == 'L') {
			units = -units;
		}

	}
	cout << total << '\n';
}