#include <fstream>
#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>

using namespace std;

#define ll long long

ifstream fin("input.txt");
ofstream fout("output.txt");

int N;
vector<pair<ll, ll>> inp, sx, sy;

ll findvm(vector<pair<ll, ll>>& sv, vector<pair<ll, ll>>& tsv) {
    ll mintv = tsv[N - 1].first, maxtv = tsv[0].first;
    vector<pair<ll, ll>> mmvs(N + 1, {0, 0});
    for (int i = N - 1; i >= 0; i--) {
        mintv = min(mintv, sv[i].second);
        maxtv = max(maxtv, sv[i].second);
        mmvs[i] = {mintv, maxtv};
    }
    mintv = tsv[N - 1].first, maxtv = tsv[0].first;
    ll vm = 0;
    for (int i = 0; i < N - 1; i++) {
        ll v = sv[i].first;
        while (i < N && sv[i].first == v) {
            mintv = min(mintv, sv[i].second);
            maxtv = max(maxtv, sv[i].second);
            i++;
        }
        i--;
        ll a1 = (v - sv[0].first) * (maxtv - mintv);
        ll a2 = 0;
        if (i < N)
            a2 = (sv[N - 1].first - sv[i + 1].first) *
                 (mmvs[i + 1].second - mmvs[i + 1].first);
        ll ta = a1 + a2;
        vm = min(vm, ta);
    }
    return vm;
}

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
    ll sxy = findvm(sx, sy);
    ll syx = findvm(sy, sx);
    orA = min(orA, sxy;
    orA = min(orA, syx));
    fout << uora - orA << '\n';
}