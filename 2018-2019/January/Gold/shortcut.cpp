#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
#include <string.h>

#define ll long long

using namespace std;

struct pt { // path to
	int f; // field
	int t; // time
	pt() {}
	pt(int f, int t) { 
		this->f = f;
		this->t = t;
	}
	bool operator<(const pt a) const {
		if (t == a.t) return f < a.f;
		return t < a.t;
	}
};

int N, M, T;
int cs[10000];
vector<pt> paths[10000];
int passes[10000];

ll dists[10000];
bool visited[10000];
ll parents[10000];
priority_queue<pt> nodes;
vector<int> children[10000];

int checkpasses(int f) {
	int pss = cs[f];
	for (int i = 0; i < children[f].size(); i++) {
		int next = children[f][i];
		pss += checkpasses(next);
	}
	passes[f] = pss;
	return pss;
}

void dijkstra() {
	memset(dists, -1, sizeof(dists));

	dists[0] = 0;
	parents[0] = -1;
	nodes.emplace(pt(0, 0));
	while (!nodes.empty()) {
		pt node = nodes.top();
		nodes.pop();
		int f = node.f;
		visited[f] = true;
		for (int i = 0; i < paths[f].size(); i++) {
			pt& next = paths[f][i];
			int nf = next.f;
			int nt = next.t;
			if (dists[f] + nt < dists[nf] || dists[nf] == -1 || (dists[f] + nt == dists[nf] && f < parents[nf])) {
				dists[nf] = dists[f] + nt;
				parents[nf] = f;
				nodes.push(next);
			}
		}
	}

	for (int i = 1; i < N; i++) {
		int p = parents[i];
		children[p].push_back(i);
	}

	checkpasses(0);
}

int main() {
	ifstream fin("shortcut.in");
	ofstream fout("shortcut.out");

	fin >> N >> M >> T;
	for (int i = 0; i < N; i++) fin >> cs[i];
	for (int i = 0; i < M; i++) {
		int a, b, t;
		fin >> a >> b >> t;
		a--, b--;
		paths[a].push_back(pt(b, t));
		paths[b].push_back(pt(a, t));
	}

	dijkstra();

	ll best = 0;
	for (int i = 0; i < N; i++) {
		ll shorten = (dists[i] - T) * passes[i];
		if (shorten > best) best = shorten;
	}

	fout << best << '\n';
}