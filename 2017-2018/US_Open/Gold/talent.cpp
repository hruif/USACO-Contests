#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;

#ifdef LOCAL_DEBUG
ifstream fin("input.txt");
ofstream fout("output.txt");
#else
ifstream fin("talent.in");
ofstream fout("talent.out");
#endif

int N, W;
int w[250], t[250];
pair<double, int> r[250];

int main() {
    fin >> N >> W;
    for (int i = 0; i < N; i++) fin >> w[i] >> t[i];
    for (int i = 0; i < N; i++) r[i] = {  (double)(t[i]) / w[i], i  };
    sort(r, r + N);

    int weights = 0;
    int talent = 0;
    int p = N - 1;
    while (weights < W) {
        int ind = r[p--].second;
        int we = w[ind], ta = t[ind];
        weights += we;
        talent += ta;
    }
    double ratio = (double)(talent) / weights;
    int intr = ratio * 1000;
    fout << intr << '\n';
}