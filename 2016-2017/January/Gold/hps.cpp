#include <iostream>
#include <fstream>

using namespace std;

int N, K;
char gs[100000];
int DP[21][100000][3];

int ltoi(char l) {
	switch (l) {
	case 'H': return 0;
	case 'P': return 1;
	case 'S': return 2;
	}
}

int main() {
	ifstream fin("hps.in");
	ofstream fout("hps.out");

	fin >> N >> K;
	for (int i = 0; i < N; i++) fin >> gs[i];

	int H = 0, P = 0, S = 0;
	for (int i = 0; i < N; i++) {
		switch (gs[i]) {
		case 'H': H++; break;
		case 'P': P++; break;
		case 'S': S++; break;
		}
		DP[0][i][0] = H, DP[0][i][1] = P, DP[0][i][2] = S;
	}

	for (int k = 1; k <= K; k++) {
		for (int g = 0; g < 3; g++) {
			DP[k][k - 1][g] = max(DP[k - 1][k - 1][0], max(DP[k - 1][k - 1][1], DP[k - 1][k - 1][2]));
			for (int i = k; i < N; i++) {
				DP[k][i][g] = max(max(DP[k][i - 1][g], DP[k - 1][i - 1][0]), max(DP[k - 1][i - 1][1], DP[k - 1][i - 1][2]));
				int gg = ltoi(gs[i]);
				if (gg == g) DP[k][i][g]++;
			}
		}
	}

	fout << max(DP[K][N - 1][0], max(DP[K][N - 1][1], DP[K][N - 1][2])) << '\n';
}