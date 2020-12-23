#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int N, K;
int dp[1005][1005];
int ans = 0;

void setdp() {
	for (int i = 0; i <= 1000; i++) {
		bool nl = i > 0;
		for (int j = 0; j <= 1000; j++) {
			bool nb = j > 0;
			if (nl) dp[i][j] += dp[i - 1][j];
			if (nb) dp[i][j] += dp[i][j - 1];
			if (nl && nb) dp[i][j] -= dp[i - 1][j - 1];
			if (dp[i][j] == K) ans++;
		}
	}
}

int main() {
	ifstream fin("paintbarn.in");
	ofstream fout("paintbarn.out");

	fin >> N >> K;
	for (int i = 0; i < N; i++) {
		int x1, y1, x2, y2;
		fin >> x1 >> y1 >> x2 >> y2;
		dp[x1][y1]++;
		dp[x1][y2]--;
		dp[x2][y1]--;
		dp[x2][y2]++;
	}

	setdp();

	fout << ans << '\n';
}