#include <iostream>
#include <fstream>

using namespace std;

int N, M;
int ps[100];
bool diff[100][100];

int main() {
	ifstream fin("revegetate.in");
	ofstream fout("revegetate.out");

	fin >> N >> M;
	for (int i = 0; i < M; i++) {
		int p1, p2;
		fin >> p1 >> p2;
		p1--, p2--;
		diff[p1][p2] = true;
		diff[p2][p1] = true;
	}

	ps[0] = 1;
	for (int i = 1; i < N; i++) {
		for (int p = 1; p <= 4; p++) {
			bool work = true;
			for (int j = 0; j < i; j++) {
				if (ps[j] == p && diff[i][j]) {
					work = false;
					break;
				}
			}
			if (work) {
				ps[i] = p;
				break;
			}
		}
	}

	for (int i = 0; i < N; i++) {
		fout << ps[i];
	}
	cout << '\n';
}