#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <string.h>
#include <unordered_set>

using namespace std;

#ifdef LOCAL
ifstream fin("input.txt");
ofstream fout("output.txt");
#else
ifstream fin("cownomics.in");
ofstream fout("cownomics.out");
#endif

int N, M;
vector<string> spotty, plain;
unordered_set<string> sss; // spotty subsequences

bool inS(unordered_set<string>& s, string& v) {
    bool ans = s.find(v) != s.end();
    return ans;
}

bool cantell(int len) {
    vector<string> vss(N), vps(N);
    bool goodpos = true;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < len; j++) {
            vss[i].push_back(spotty[i][j]);
        }
        sss.insert(vss[i]);
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < len; j++) {
            vps[i].push_back(plain[i][j]);
        }
        if (inS(sss, vps[i])) goodpos = false;
    }
    sss.clear();
    if (goodpos) return true;
    for (int start = 1; start < M - len + 1; start++) {
        bool goodpos = true;
        for (int i = 0; i < N; i++) {
            vss[i].erase(vss[i].begin());
            vss[i].push_back(spotty[i][start + len - 1]);
            sss.insert(vss[i]);
        }
        for (int i = 0; i < N; i++) {
            vps[i].erase(vps[i].begin());
            vps[i].push_back(plain[i][start + len - 1]);
            if (inS(sss, vps[i])) goodpos = false;
        }
        sss.clear();
        if (goodpos) return true;
    }
    return false;
}

int main() {
    fin >> N >> M;
    spotty.resize(N); plain.resize(N);
    for (int i = 0; i < N; i++) fin >> spotty[i];
    for (int i = 0; i < N; i++) fin >> plain[i];
    int l = 0, r = M;
    while (l < r - 1) {
        int mid = (l + r) / 2;
        if (cantell(mid)) r = mid;
        else l = mid;
    }
    fout << r << '\n';
}