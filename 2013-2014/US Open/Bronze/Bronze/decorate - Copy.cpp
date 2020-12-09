#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int N, M;
int con = 0;
int fs[50000];
int js[50000];
char pasts[50000];
vector<vector<int>> paths;

bool foundH(int p, char l) {
	if (pasts[p] != 0) return pasts[p] == l;
	pasts[p] = l;
	if (l == 'F') fs[con]++;
	else js[con]++;
	char nl = l == 'F' ? 'J' : 'F';
	for (int i = 0; i < paths[p].size(); i++) {
		if (!foundH(paths[p][i], nl)) {
			return false;
		}
	}
	return true;
}

int main() {
	ifstream fin("decorate.in");
	ofstream fout("decorate.out");

	fin >> N >> M;
	paths.resize(N);
	for (int i = 0; i < M; i++) {
		int A, B;
		fin >> A >> B;
		paths[A - 1].push_back(B - 1);
		paths[B - 1].push_back(A - 1);
	}
	bool impossible = false;
	for (int i = 0; i < N; i++) {
		if (pasts[i] != 0) {
			continue;
		}
		if (!foundH(0, 'J')) {
			impossible = true;
			break;
		}
		con++;
	}
	if (impossible) {
		fout << -1 << '\n';
	}
	else {
		int total = 0;
		for (int i = 0; i < con; i++) {
			total += max(fs[i], js[i]);
		}
		fout << total << '\n';
	}
}