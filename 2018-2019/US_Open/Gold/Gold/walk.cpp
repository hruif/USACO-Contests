#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

#ifdef LOCAL_DEBUG
ifstream fin("input.txt");
ofstream fout("output.txt");
#else
ifstream fin("walk.in");
ofstream fout("walk.out");
#endif

#define XM 2019201913LL
#define YM 2019201949LL
#define MOD 2019201997LL
#define ll long long

int N, K;
ll dists[7500];
bool visited[7500];

int main() {
    fin >> N >> K;

    for (int i = 0; i < N; i++) dists[i] = MOD;
    for (int i = 0; i < N; i++) {
        int mini = -1;
        for (int j = 0; j < N; j++) {
            if (!visited[j] && (mini == -1 || dists[j] < dists[mini])) mini = j;
        }
        visited[mini] = true;
        for (int j = 0; j < N; j++) {
            if (!visited[j]) {
                dists[j] = min(dists[j], (min(j + 1, mini + 1) * XM
                     + max(j + 1, mini + 1) * YM) % MOD);
            }
        }
    }
    sort(dists, dists + N);
    fout << dists[N - K] << '\n';
}