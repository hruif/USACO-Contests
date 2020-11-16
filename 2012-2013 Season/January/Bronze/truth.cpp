#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

int N, M;
int cows[1000];

int main() {
	memset(cows, -1, sizeof(cows));
	ifstream fin("input.in");
	fin >> N >> M;
	int breakoff = 0;
	for (int i = 0; i < M; i++) {
		breakoff = i;
		int x, y;
		char t;
		fin >> x >> y >> t;
		if (t == 'T') {
			if (cows[x] == 1) {
				break;
			}
			if (cows[y] == 1) {
				break;
			}
			cows[x] = 0;
			cows[y] = 0;
		}
		else {
			if (cows[x] == 0) {
				break;
			}
			if (cows[y] == 0) {
				break;
			}
			cows[x] = 1;
			cows[y] = 1;
		}
	}
	cout << breakoff << '\n';
}