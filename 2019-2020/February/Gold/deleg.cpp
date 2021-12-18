#include <iostream>
#include <fstream>
#include <vector>
#include <set>
using namespace std;

//#define LOCAL

#ifndef LOCAL
ifstream fin("deleg.in");
ofstream fout("deleg.out");
#else
#define fin cin
#define fout cout
#endif

int N;
vector<vector<int>> edges;

int dfs(int node, int par, int k) {
    multiset<int> rems;
    for (auto x : edges[node]) {
        if (x == par) continue;
        int r = dfs(x, node, k);
        if (r >= k) r -= k;
        if (r == -1) return -1;
        if (rems.find(k - r) != rems.end()) rems.erase(rems.find(k - r));
        else if (r != 0) rems.insert(r);
    }
    if (rems.size() > 1) return -1;
    if (rems.empty()) return 1;
    else return (*rems.begin()) + 1;

}

bool sieve[200000];
vector<long long> primes;

int main() {
    for (long long i = 2; i < 200000; i++) {
        if (!sieve[i]) {
            primes.push_back(i);
            for (long long j = i * i; j < 200000; j += i) sieve[j] = true;
        }
    }

    fin >> N;
    edges.resize(N);
    for (int i = 0; i < N - 1; i++) {
        int a, b;
        fin >> a >> b;
        a--; b--;
        edges[a].push_back(b);
        edges[b].push_back(a);
    }
    vector<bool> noworks(N * 2, false);
    for (long long i = 1; i < N; i++) {
        if (noworks[i]) continue;
        if ((N - 1) % i == 0) {
            if (!(dfs(0, -1, i) == 1)) {
                noworks[i] = true;
                for (auto x : primes) {
                    if (x * i > N + 2) break;
                    noworks[x * i] = true;
                }
            }
        }
        else noworks[i] = true;
    }
    for (int i = 1; i < N; i++) fout << (!noworks[i] ? 1 : 0);
    fout << '\n';
}