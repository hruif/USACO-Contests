#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string.h>

using namespace std;

#define f first
#define s second
#define ll long long

#ifdef LOCAL
ifstream fin("input.txt");
ofstream fout("output.txt");
#else
ifstream fin("radio.in");
ofstream fout("radio.out");
#endif

int N, M;
int fx, fy, bx, by;
char FJ[1000], B[1000];
ll dp[1001][1001];
pair<int, int> fjpos[1001], bpos[1001];

ll solve(int fi, int bi) {
    if (dp[fi][bi] != -1) return dp[fi][bi];
    ll xdis = abs(fjpos[fi].f - bpos[bi].f);
    ll ydis = abs(fjpos[fi].s - bpos[bi].s);
    ll en = xdis * xdis + ydis * ydis;

    ll add = 10000000000;
    if (fi < N) add = min(add, solve(fi + 1, bi));
    if (bi < M) add = min(add, solve(fi, bi + 1));
    if (fi < N && bi < M) add = min(add, solve(fi + 1, bi + 1));
    if (fi == N && bi == M) return en;
    dp[fi][bi] = en + add;
    return en + add;
}

int main() {
    memset(dp, -1, sizeof(dp));

    fin >> N >> M;
    fin >> fx >> fy >> bx >> by;
    for (int i = 0; i < N; i++) fin >> FJ[i];
    for (int i = 0; i < M; i++) fin >> B[i];
    bpos[0].f = bx; bpos[0].s = by;
    fjpos[0].f = fx; fjpos[0].s = fy;
    for (int i = 1; i <= N; i++) {
        fjpos[i] = fjpos[i - 1];
        switch (FJ[i - 1]) {
            case 'N': fjpos[i].s++; break;
            case 'W': fjpos[i].f--; break;
            case 'E': fjpos[i].f++; break;
            case 'S': fjpos[i].s--; break;
        }
    }
    for (int i = 1; i <= M; i++) {
        bpos[i] = bpos[i - 1];
        switch (B[i - 1]) {
            case 'N': bpos[i].s++; break;
            case 'W': bpos[i].f--; break;
            case 'E': bpos[i].f++; break;
            case 'S': bpos[i].s--; break;
        }
    }
    fout << min(min(solve(0, 1), solve(1, 0)), solve(1, 1))<< '\n';
}