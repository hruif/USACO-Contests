#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

#ifdef LOCAL
ifstream fin("input.txt");
ofstream fout("output.txt");
#else
#define fin cin
#define fout cout
#endif

int N;
int paint[300];
int dp[300][300];

int main() {
    fin >> N;
    for (int i = 0; i < N; i++) fin >> paint[i];
    
    for (int i = N - 1; i >= 0; i--) {
        for (int j = i + 1; j < N; j++) {
            if (paint[i] == paint[j]) dp[i][j] = dp[i + 1][j - 1] + 1;
            for (int k = i + 1; k < j; k++) dp[i][j] = max(dp[i][j], dp[i][k] + dp[k][j]);
        }
    }

    fout << N - dp[0][N - 1] << '\n';
}