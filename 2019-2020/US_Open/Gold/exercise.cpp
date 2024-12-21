#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

#define ll long long

#ifdef LOCAL_DEBUG
ifstream fin("input.txt");
ofstream fout("output.txt");
#else
ifstream fin("exercise.in");
ofstream fout("exercise.out");
#endif

int N, M;
vector<int> primes;

void findprimes(int n) {
    vector<int> comp(n + 1);
    for (int i = 2; i <= n; i++) {
        if (!comp[i]) {
            primes.push_back(i);
            for (int j = i * 2; j <= n; j += i) {
                comp[j] = 1;
            }
        }
    }
}

vector<vector<ll>> res;

int main() {
    fin >> N >> M;

    findprimes(N);
    res.resize(primes.size() + 1, vector<ll>(N + 1, 0));
    for (int i = 0; i < N + 1; i++) {
        res[0][i] = 1;
    }

    if (primes.size() == 0) {
        fout << "1\n";
    }
    else {
    for (int i = 1; i <= primes.size(); i++) {
        for (int j = 0; j <= N; j++) {
            res[i][j] = res[i - 1][j];
            int val = primes[i - 1];
            while (val <= j) {
                res[i][j] += val * res[i - 1][j - val];
                res[i][j] %= M;
                val *= primes[i - 1];
            }
        }
    }

    fout << res[primes.size()][N] % M << '\n';
    }
}