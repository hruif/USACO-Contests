#include <iostream>
#include <fstream>

using namespace std;

int N;
char grid[100][100];
int csingle[100][100];
int hsingle[100][100];
int cinds[10000];
int hinds[10000];

int main() {
	ifstream fin("cowart.in");
	ofstream fout("cowart.out");
	fin >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			fin >> grid[i][j];
		}
	}
	int cowcnt = 0;
	int humcnt = 0;
	int cowi = 1;
	int humi = 1;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			char c = grid[i][j];
			bool csame = false;
			bool hsame = false;
			int fcowt = 0;
			int fhumt = 0;
			int fcowl = 0;
			int fhuml = 0;
			if (c == 'R') {
				if (i > 0) {
					if (grid[i - 1][j] == c) {
						hsame = true;
						csame = true;
						fcowt = csingle[i - 1][j];
						fhumt = hsingle[i - 1][j];
					}
					if (grid[i - 1][j] == 'G') {
						csame = true;
						fcowt = csingle[i - 1][j];
					}
				}
				if (j > 0) {
					if (grid[i][j - 1] == c) {
						hsame = true;
						csame = true;
						fcowl = csingle[i][j - 1];
						fhuml = hsingle[i][j - 1];
					}
					if (grid[i][j - 1] == 'G') {
						csame = true;
						fcowl = csingle[i - 1][j];
					}
				}
			}
			if (c == 'G') {
				if (i > 0) {
					if (grid[i - 1][j] == c) {
						hsame = true;
						csame = true;
						fcowt = csingle[i - 1][j];
						fhumt = hsingle[i - 1][j];
					}
					if (grid[i - 1][j] == 'R') {
						csame = true;
						fcowt = csingle[i - 1][j];
					}
				}
				if (j > 0) {
					if (grid[i][j - 1] == c) {
						hsame = true;
						csame = true;
						fcowl = csingle[i][j - 1];
						fhuml = hsingle[i][j - 1];
					}
					if (grid[i][j - 1] == 'R') {
						csame = true;
						fcowl = csingle[i][j - 1];
					}
				}
			}
			if (c == 'B') {
				if (i > 0) {
					if (grid[i - 1][j] == c) {
						hsame = true;
						csame = true;
						fcowt = csingle[i - 1][j];
						fhumt = hsingle[i - 1][j];
					}
				}
				if (j > 0) {
					if (grid[i][j - 1] == c) {
						hsame = true;
						csame = true;
						fcowl = csingle[i][j - 1];
						fhuml = hsingle[i][j - 1];
					}
				}
			}
			if (fcowt != 0 && fcowl != 0 && fcowt != fcowl) cowcnt--;
			if (fhumt != 0 && fhuml != 0 && fhumt != fhuml) humcnt--;
			if (!csame) {
				cowcnt++;
				csingle[i][j] = cowi++;
			}
			else {
				if (j > 0) {
					csingle[i][j] = csingle[i][j - 1];
				}
				else {
					csingle[i][j] = csingle[i - 1][j];
				}
			}
			if (!hsame) {
				humcnt++;
				hsingle[i][j] = humi++;
			}
			else {
				if (j > 0) {
					hsingle[i][j] = hsingle[i][j - 1];
				}
				else {
					hsingle[i][j] = hsingle[i - 1][j];
				}
			}
		}
	}
	cout << humcnt << ' ' << cowcnt << '\n';
}