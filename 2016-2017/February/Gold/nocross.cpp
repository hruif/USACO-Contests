#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;

int N;
int cs[2][1000];
int dp[1000][1000];
vector<int> st;

void updst(int k, int x) {
	int sn = st.size() / 2;
	k += sn;
	st[k] = x;
	for (k /= 2; k >= 1; k /= 2) {
		st[k] = max(st[k * 2], st[k * 2 + 1]);
	}
}

int findmax(int a, int b) {
	int sn = st.size() / 2;
	a += sn, b += sn;
	int s = 0;
	while (a <= b) {
		if (a % 2 == 1) s = max(s, st[a++]);
		if (b % 2 == 0) s = max(s, st[b--]);
		a /= 2, b /= 2;
	}
	return s;
}

void setst(int n, int* arr) {
	int sn = 1;
	while (sn < n) sn *= 2;
	sn *= 2;
	st.resize(sn, 0);
	for (int i = 0; i < n; i++) {
		updst(i, arr[i]);
	}
}

int main() {
	ifstream fin("nocross.in");
	ofstream fout("nocross.out");

	fin >> N;
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < N; j++) {
			fin >> cs[i][j];
			cs[i][j]--;
		}
	}

	for (int i = 0; i < N; i++) {
		if (abs(cs[0][0] - cs[1][i]) <= 4) dp[0][i] = 1;
	}
	for (int i = 1; i < N; i++) {
		st.clear();
		setst(N, dp[i - 1]);
		for (int j = 0; j < N; j++) {
			dp[i][j] = findmax(0, j - 1);
			if (abs(cs[0][i] - cs[1][j]) <= 4) dp[i][j]++;
			dp[i][j] = max(dp[i][j], dp[i - 1][j]);
		}
	}
	st.clear();
	setst(N, dp[N - 1]);
	fout << findmax(0, N - 1) << '\n';
}