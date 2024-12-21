#include <iostream>
#include <fstream>
#include <string.h>
#include <vector>
#include <algorithm>

using namespace std;

#ifdef LOCAL_DEBUG
ifstream fin("input.txt");
ofstream fout("output.txt");
#else
ifstream fin("snakes.in");
ofstream fout("snakes.out");
#endif

#define ll long long

int N, K;
int a[400];
int vals[1000001];
vector<int> sa;

int main() {
    fin >> N >> K;
    for (int i = 0; i < N; i++) fin >> a[i];
    for (int i = 0; i < N; i++) {
        if (vals[a[i]]) continue;
        sa.push_back(a[i]);
        vals[a[i]]++;
    }
    sort(sa.begin(), sa.end());

    vector<vector<vector<ll> > > dp(1, vector<vector<ll> >(N, vector<ll>(sa.size(), 1000000000)));
    vector<ll> pmax(N + 1, 1000000000);
    for (int k = 0; k < sa.size(); k++) {
        if (sa[k] >= a[0]) {
            dp[0][0][k] = sa[k] - a[0];
            pmax[0] = min(pmax[0], dp[0][0][k]);
        }
    }
    for (int j = 1; j < N; j++) {
        for (int k = 0; k < sa.size(); k++) {
            if (sa[k] >= a[j]) {
                dp[0][j][k] = dp[0][j - 1][k] + sa[k] - a[j];
                if (dp[0][j][k] < 10000000000) pmax[j] = min(pmax[j], dp[0][j][k]);
            }
        }
    }
    for (int i = 1; i <= K; i++) {
        ll pnpm = 1000000000;
        for (int k = 0; k < sa.size(); k++) {
            if (sa[k] >= a[0]) {
                dp[0][0][k] = sa[k] - a[0];
                pnpm = min(pnpm, dp[0][0][k]);
            }
        }
        for (int j = 1; j < N; j++) {
            ll npm = 1000000000;
            for (int k = 0; k < sa.size(); k++) {
                if (sa[k] >= a[j]) {
                    dp[0][j][k] = min(pmax[j - 1], dp[0][j - 1][k]) + sa[k] - a[j];
                    npm = min(npm, dp[0][j][k]);
                }
            }
            pmax[j - 1] = pnpm;
            pnpm = npm;
        }
        pmax[N - 1] = pnpm;
    }

    fout << pmax[N - 1] << '\n';
}