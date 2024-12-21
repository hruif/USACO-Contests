#include <fstream>
#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>

using namespace std;

#define ll long long

ifstream fin("split.in");
ofstream fout("split.out");

int N;
vector<pair<ll, ll>> inp, sx, sy;

int main() {
    fin >> N;
    inp.resize(N);
    sx.resize(N);
    sy.resize(N);
    for (int i = 0; i < N; i++) {
        fin >> inp[i].first >> inp[i].second;
    }
    sx = inp;
    for (int i = 0; i < N; i++) {
        sy[i].first = inp[i].second;
        sy[i].second = inp[i].first;
    }
    sort(sx.begin(), sx.end());
    sort(sy.begin(), sy.end());
    ll minx = sx[0].first, maxx = sx[N - 1].first, miny = sy[0].first,
       maxy = sy[N - 1].first;
    ll orA = (maxx - minx) * (maxy - miny);  // original area

    ll uora = orA;
    miny = sy[N - 1].first, maxy = sy[0].first;
    vector<pair<ll, ll>> mmys(N + 1, {0, 0});
    for (int i = N - 1; i >= 0; i--) {
        miny = min(miny, sx[i].second);
        maxy = max(maxy, sx[i].second);
        mmys[i] = {miny, maxy};
    }
    miny = sy[N - 1].first, maxy = sy[0].first;
    for (int i = 0; i < N - 1; i++) {
        ll x = sx[i].first;
        while (i < N && sx[i].first == x) {
            miny = min(miny, sx[i].second);
            maxy = max(maxy, sx[i].second);
            i++;
        }
        i--;
        ll a1 = (x - sx[0].first) * (maxy - miny);
        ll a2 = 0;
        if (i < N)
            a2 = (sx[N - 1].first - sx[i + 1].first) *
                 (mmys[i + 1].second - mmys[i + 1].first);
        ll ta = a1 + a2;
        orA = min(orA, ta);
    }

    minx = sx[N - 1].first, maxx = sx[0].first;
    vector<pair<ll, ll>> mmxs(N + 1, {0, 0});
    for (int i = N - 1; i >= 0; i--) {
        minx = min(minx, sy[i].second);
        maxx = max(maxx, sy[i].second);
        mmxs[i] = {minx, maxx};
    }
    minx = sx[N - 1].first, maxx = sx[0].first;
    for (int i = 0; i < N - 1; i++) {
        ll y = sy[i].first;
        while (i < N && sy[i].first == y) {
            minx = min(minx, sy[i].second);
            maxx = max(maxx, sy[i].second);
            i++;
        }
        i--;
        ll a1 = (y - sy[0].first) * (maxx - minx);
        ll a2 = 0;
        if (i < N)
            a2 = (sy[N - 1].first - sy[i + 1].first) *
                 (mmxs[i + 1].second - mmxs[i + 1].first);
        ll ta = a1 + a2;
        orA = min(orA, ta);
    }
    fout << uora - orA << '\n';
}