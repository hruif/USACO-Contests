#include <iostream>
#include <fstream>
#include <vector>
#include <utility>

using namespace std;
using pii = pair<int, int>;

#define f first
#define s second

#ifdef LOCAL
ifstream fin("input.txt");
ofstream fout("output.txt");
#else
ifstream fin("art2.in");
ofstream fout("art2.out");
#endif

int N, md;
int art[100000];
vector<pii> cols;

bool validRange(int l, int r, int d) {
    md = max(md, d);
    for (int i = l + 1; i < r; i++) {
        int c = art[i];
        int cl = cols[c].f, cr = cols[c].s;
        if (cl == l) continue;
        if (cl < l || cr > r) return false;
        int pd = c == 0 ? 0 : 1;
        if (!validRange(cl, cr, d + pd)) return false;
        i = cr;
    }
    return true;
}

int main() {
    fin >> N;
    cols.resize(N + 1, {  -1, -1  });
    for (int i = 0; i < N; i++) fin >> art[i];
    for (int i = 0; i < N; i++) {
        int c = art[i];
        if (cols[c].f == -1) cols[c].f = i;
        cols[c].s = i;
    }
    bool valid = true;
    for (int i = 0; i < N; i++) {
        int c = art[i];
        int l = cols[c].f, r = cols[c].s;
        int d = c == 0 ? 0 : 1;
        if (!validRange(l, r, d)) {
            valid = false;
            break;
        }
        i = r;
    }
    if (valid) fout << md << '\n';
    else fout << -1 << '\n';
}