#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

ifstream fin("closing.in");
ofstream fout("closing.out");
//ifstream fin("input.txt");
//ofstream fout("output.txt");

int N, M;
vector<int> closing;
vector<bool> open;
vector<vector<int>> con;

vector<int> link, us;
int findrep(int x) {
    while (x != link[x]) x = link[x];
    return x;
}

bool sameu(int a, int b) {
    return findrep(a) == findrep(b);
}

void unite(int a, int b) {
    a = findrep(a);
    b = findrep(b);
    if (us[a] < us[b]) swap(a, b);
    us[a] += us[b];
    link[b] = a;
}

int main() {
    fin >> N >> M;
    con.resize(N);
    open.resize(N, false);
    link.resize(N); us.resize(N, 1);
    for (int i = 0; i < N; i++) link[i] = i;
    for (int i = 0; i < M; i++) {
        int a, b;
        fin >> a >> b;
        a--; b--;
        con[a].push_back(b);
        con[b].push_back(a);
    }
    closing.resize(N);
    for (int i = 0; i < N; i++) fin >> closing[i];

    vector<string> ans(N);
    for (int i = N - 1; i >= 0; i--) {
        int toadd = closing[i] - 1;
        open[toadd] = true;
        for (int j = 0; j < con[toadd].size(); j++) {
            if (!sameu(toadd, con[toadd][j]) && open[con[toadd][j]]) unite(toadd, con[toadd][j]);
        }
        if (us[findrep(toadd)] == N - i) ans[i] = "YES\n";
        else ans[i] = "NO\n";
    }
    for (int i = 0; i < N; i++) fout << ans[i];
}