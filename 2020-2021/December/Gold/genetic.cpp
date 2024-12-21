#include <iostream>
#include <fstream>
#include <string>

using namespace std;

#define ll long long
#define MOD 1000000007

#ifdef LOCAL
ifstream fin("input.txt");
ofstream fout("output.txt");
#else
#define fin cin
#define fout cout
#endif

int intS[100000];
ll dp[100000][4][4][4];

int main() {
    string S;
    fin >> S;
    for (int i = 0; i < S.size(); i++) {
        int val;
        switch (S[i]) {
            case 'A': val = 0; break;
            case 'G': val = 1; break;
            case 'C': val = 2; break;
            case 'T': val = 3; break;
            case '?': val = 4; break;
        }
        intS[i] = val;
    }

    for (int i = 0; i < S.size(); i++) {
        for (int j = 0; j < 4; j++) {
            for (int k = 0; k < 4; k++) {
                for (int l = 0; l < 4; l++) {
                    for (int m = 0; m < 4; m++) {
                        if (m == intS[i] || intS[i] == 4) {
                            if (i == 0) {
                                dp[i][j][m][m] = 1;
                            }
                            else {
                                if (l != m) {
                                    dp[i][j][k][m] += dp[i - 1][j][k][l];
                                    dp[i][j][k][m] %= MOD;
                                }
                                if (j == l) {
                                    dp[i][k][m][m] += dp[i - 1][j][k][l];
                                    dp[i][k][m][m] %= MOD;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    ll total = 0;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            total += dp[S.size() - 1][i][j][i];
        }
    }
    fout << total % MOD << '\n';
}