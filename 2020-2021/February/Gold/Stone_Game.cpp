#include <iostream>
#include <fstream>
#include <algorithm>

#define ll long long

using namespace std;

#ifdef LOCAL
ifstream fin("input.txt");
ofstream fout("output.txt");
#else
#define fin cin
#define fout cout
#endif

int N;
int a[100000];
int vals[1000001];
int vpsum[1000001];
int groupvals[1000001];

int main() {
    fin >> N;
    for (int i = 0; i < N; i++) fin >> a[i];
    sort(a, a + N);
    for (int i = 0; i < N; i++) vals[a[i]]++;
    vpsum[0] = vals[0];
    for (int i = 1; i <= 1000000; i++) vpsum[i] = vals[i] + vpsum[i - 1];

    ll ans = 0;
    for (int s = 1; s <= a[N - 1]; s++) {
        int x = 0;
        while (s * x <= 1000000) {
            int sx = s * x;
            int piles = vpsum[min(1000000, sx + s - 1)] - vpsum[sx - 1];
            groupvals[x] = piles;
            x++;
        }
        int odds = 0;
        bool adjodds = false, podd = false;
        int cnt = -1;
        for (int i = x - 1; i > 0; i--) {
            if (groupvals[i] % 2) {
                if (podd) adjodds = true;
                else podd = true;
                if (cnt == -1) cnt = groupvals[i];
                odds++;
            }
            else podd = false;
        }
        if (groupvals[1] % 2 && odds == 1) {
            if (podd) adjodds = true;
        }
        if (adjodds && odds <= 2) ans += cnt;
    }
    fout << ans << '\n';
}