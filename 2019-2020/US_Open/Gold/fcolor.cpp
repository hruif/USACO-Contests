#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

#ifdef LOCAL_DEBUG
ifstream fin("input.txt");
ofstream fout("output.txt");
#else
ifstream fin("fcolor.in");
ofstream fout("fcolor.out");
#endif

int N, M;
vector<int> p;
vector<vector<int>> ad, ch;
queue<int> q;

void merge(int a, int b) {
    a = p[a], b = p[b];
    if (ch[a].size() < ch[b].size()) swap(a, b);
    for (auto i : ch[b]) {
        p[i] = a;
        ch[a].push_back(i);
    }
    ad[a].insert(ad[a].end(), ad[b].begin(), ad[b].end());
    ad[b].clear();
    if (ad[a].size() > 1) q.push(a);
}

int main() {
    fin >> N >> M;
    ad.resize(N);
    p.resize(N);
    ch.resize(N);
    for (int i = 0; i < M; i++) {
        int a, b;
        fin >> a >> b;
        a--, b--;
        ad[a].push_back(b);
    }
    for (int i = 0; i < N; i++) {
        p[i] = i;
        ch[i].push_back(i);
        if (ad[i].size() > 1) q.push(i);
    }

    while (!q.empty()) {
        int x = q.front();
        if (ad[x].size() <= 1) {
            q.pop(); 
            continue;
        }
        int a = ad[x].back();
        ad[x].pop_back();
        int b = ad[x].back();
        if (p[a] == p[b]) continue;
        merge(a, b);
    }

    int cos = 0;
    vector<int> cols(N, 0);
    for (int i = 0; i < N; i++) {
        if (cols[p[i]] == 0) cols[p[i]] = ++cos;
        fout << cols[p[i]] << '\n';
    }
}