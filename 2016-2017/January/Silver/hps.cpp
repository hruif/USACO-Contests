#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

int N;
char fj[100000];
int wins[100000][3];

int main() {
	ifstream fin("hps.in");
	ofstream fout("hps.out");

	fin >> N;
	for (int i = 0; i < N; i++) {
		fin >> fj[i];
	}

	if (fj[0] == 'H') wins[0][0]++;
	else if (fj[0] == 'P') wins[0][1]++;
	else wins[0][2]++;
	for (int i = 1; i < N; i++) {
		wins[i][0] = wins[i - 1][0];
		wins[i][1] = wins[i - 1][1];
		wins[i][2] = wins[i - 1][2];

		switch (fj[i]) {
		case 'H':
			wins[i][0]++;
			break;
		case 'P':
			wins[i][1]++;
			break;
		case 'S':
			wins[i][2]++;
			break;
		}
	}
	int ts[3] = { wins[N - 1][0], wins[N - 1][1], wins[N - 1][2] };

	int maxwins = 0;
	for (int i = 0; i < N - 1; i++) {
		for (int j = 0; j < 3; j++) {
			int w1 = wins[i][j];
			for (int k = 0; k < 3; k++) {
				int w2 = ts[k] - wins[i][k];
				maxwins = max(maxwins, w1 + w2);
			}
		}
	}

	fout << maxwins << '\n';
}