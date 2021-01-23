#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <queue>
#include <algorithm>

using namespace std;

int N, Q;
vector<pair<int, int>> par;
vector<vector<pair<int, int>>> con;

bool sortgreater(int& a, int& b) {
	return a < b;
}

vector<bool> visited;
void setpars(vector<vector<pair<int, int>>>& connected) {
	int root = 0;
	int cs = connected.size();
	par.resize(cs, make_pair(-1, 0));
	visited.resize(cs, false);
	queue<int> nodes;
	nodes.push(0);
	while (!nodes.empty()) {
		int node = nodes.front();
		nodes.pop();
		if (visited[node]) continue;
		visited[node] = true;
		for (int i = 0; i < connected[node].size(); i++) {
			int next = connected[node][i].first;
			if (!visited[next]) {
				par[next] = make_pair(node, connected[node][i].second);
				visited[next] = true;
				nodes.push(next);
			}
		}
	}
}

vector<int> sts;
int setsts(int node) { // set subtree sizes
	int size = 1;
	for (int i = 0; i < con[node].size(); i++) {
		if (con[node][i].first == par[node].first) continue;
		size += setsts(con[node][i].first);
	}
	sts[node] = size;
	return size;
}

int p = 0;
vector<int> oton; // original to new
void setnewvals(int node) {
	oton[node] = p++;
	vector<pair<int, int>> tocheck;
	for (int i = 0; i < con[node].size(); i++) {
		int next = con[node][i].first;
		if (next == par[node].first) continue;
		tocheck.push_back(make_pair(sts[next], next));
	}
	sort(tocheck.begin(), tocheck.end());
	for (int i = 0; i < tocheck.size(); i++) {
		setnewvals(tocheck[i].second);
	}
}

vector<pair<int, int>> nps;
void setnps() {
	for (int i = 0; i < par.size(); i++) {
		nps[oton[i]] = make_pair(oton[par[i].first], par[i].second);
	}
}

vector<vector<pair<int, int>>> ancs; // first = anc ind, second = min rel
void setancs() {
	for (int i = 1; i < N; i++) {
		ancs[i].push_back(nps[i]);
	}

	int e = 1;
	int d = 2;
	while (e < N) {
		for (int i = 0; i < N; i++) {
			int as = ancs[i].size();
			if (as == e && ancs[as - 1].size() == e) {
				ancs[i].push_back(make_pair(ancs[ancs[i][e - 1].first][e - 1].first,// 2^e ancestor = 2^(e - 1) ancestor of 2^(e - 1) ancestor
					min(ancs[i][e - 1].second, ancs[ancs[i][e - 1].first][e - 1].second))); 
			}
		}
	}
}

int findviews

int main() {
	ifstream fin("mootube.in");
	ofstream fout("mootube.out");

	fin >> N >> Q;
	con.resize(N);
	for (int i = 0; i < N - 1; i++) {
		int p, q, r;
		cin >> p >> q >> r;
		p--, q--;
		con[p].push_back(make_pair(q, r));
		con[q].push_back(make_pair(p, r));
	}

	par.resize(N); setpars(con);
	sts.resize(N); setsts(0);
	oton.resize(N);	setnewvals(0);
	nps.resize(N); setnps();
	ancs.resize(N); setancs;
	
	for (int i = 0; i < Q; i++) {

	}
}