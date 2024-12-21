#include <iostream>
#include <fstream>
#include <vector>
#include <set>

using namespace std;

ifstream fin("248.in");
ofstream fout("248.out");
//ifstream fin("input.txt");
//ofstream fout("output.txt");

int N;
int a[248];
vector<vector<int>> dp;

int main() {
    fin >> N;
    for (int i = 0; i < N; i++) fin >> a[i];
    dp.resize(N, vector<int>(100, -1));
    for (int i = 0; i < N; i++) {
        dp[i][a[i]] = i;
        int p = i - 1;
        int v = a[i];
        while (p >= 0) {
            if (dp[p][v] == -1) {
                break;
            }
            else {
                dp[i][v + 1] = dp[p][v];
                v++;
                p = dp[i][v] - 1;
            }
        }
    }
    int mv = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < 100; j++) {
            if (dp[i][j] != -1) mv = max(mv, j);
        }
    }
    fout << mv << '\n';
}