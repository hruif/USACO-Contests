#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

int N, K;
vector<vector<int>> con;
vector<int> par;
vector<bool> isExit;

void setpar(int node) {
	for (int i = 0; i < con[node].size(); i++) {
		int next = con[node][i];
		if (next == par[node]) continue;
		par[next] = node;
		setpar(next);
	}
}

int main() {
	ifstream fin("atlarge.in");
	ofstream fout("atlarge.out");

	fin >> N >> K;
	con.resize(N); isExit.resize(N, false);
	K--;
	for (int i = 0; i < N - 1; i++) {
		int a, b;
		fin >> a >> b;
		a--, b--;
		con[a].push_back(b);
		con[b].push_back(a);
	}
	for (int i = 0; i < N; i++) {
		if (con[i].size() == 1) isExit[i] = true;
	}
	if (isExit[K]) {
		fout << "1\n";
	}
	else {
		par.resize(N, -1); setpar(K);
		par[K] = K;
		vector<int> b{ K };
		vector<int> f;
		int cnt = 0;
		vector<bool> fv(N, false);
		for (int i = 0; i < N; i++) {
			if (isExit[i]) {
				f.push_back(i);
				fv[i] = true;
			}
		}
		queue<pair<vector<int>, vector<int>>> p;
		p.push(make_pair(b, f));
		while (!p.empty()) {
			vector<int> cb = p.front().first, cf = p.front().second;
			p.pop();
			vector<int> nb, nf;
			for (int i = 0; i < cf.size(); i++) {
				int parent = par[cf[i]];
				if (!fv[parent]) {
					fv[parent] = true;
					nf.push_back(parent);
				}
			}
			for (int i = 0; i < cb.size(); i++) {
				int cur = cb[i];
				for (int j = 0; j < con[cur].size(); j++) {
					int next = con[cur][j];
					if (next == par[cur]) continue;
					if (fv[next]) cnt++;
					else nb.push_back(next);
				}
			}
			if (nb.size()) p.push(make_pair(nb, nf));
		}
		fout << cnt << '\n';
	}
}