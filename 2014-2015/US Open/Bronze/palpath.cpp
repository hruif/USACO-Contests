#include <iostream>
#include <fstream>
#include <unordered_set>

using namespace std;

long long N, total;
char grid[18][18];
unordered_set<string> us;
unordered_set<string> usf;
string s;

void dfstl(int x, int y) {
	s.push_back(grid[x][y]);
	if (s.size() == N) {
		us.insert(s);
		s.pop_back();
		return;
	}

	if (x < N - 1) {
		dfstl(x + 1, y);
	}
	if (y < N - 1) {
		dfstl(x, y + 1);
	}
	s.pop_back();
}

void dfsbr(int x, int y) {
	s.push_back(grid[x][y]);
	if (s.size() == N) {
		if (usf.find(s) == usf.end() && us.find(s) != us.end()) {
			usf.insert(s);
			total++;
		}
		s.pop_back();
		return;
	}

	if (x > 0) {
		dfsbr(x - 1, y);
	}
	if (y > 0) {
		dfsbr(x, y - 1);
	}
	s.pop_back();
}

int main() {
	ifstream fin("palpath.in");
	ofstream fout("palpath.out");

	fin >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) { 
			fin >> grid[i][j];
		}
	}

	s.clear();
	dfstl(0, 0);
	s.clear();
	dfsbr(N - 1, N - 1);

	fout << total << '\n';
}