#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <string.h>

using namespace std;

int N, M;
int cf[1000][2];
double ratios[1000];
vector<vector<pair<int, int>>> con;

int pars[1000];
void dijkstra(int node, int c, int f) {
	for (int i = 0; i < con[node].size(); i++) {
		pair<int, int> next = con[node][i];
		int nn = next.first, ne = next.second;
		int nc = c + cf[ne][0];
		int nf = f + cf[ne][1];
		double ratio = nf; ratio /= nc;
		if (ratio > ratios[nn]) {
			pars[nn] = node;
			ratios[nn] = ratio;
			dijkstra(nn, nc, nf);
		}
	}
}

int main() {
	ifstream fin("pump.in");
	ofstream fout("pump.out");

	fin >> N >> M;
	con.resize(N);
	for (int i = 0; i < M; i++) {
		int a, b, c, f;
		fin >> a >> b >> c >> f;
		a--, b--;
		cf[i][0] = c; cf[i][1] = f;
		con[a].push_back(make_pair(a, i));
		con[b].push_back(make_pair(a, i));
	}

	memset(pars, -1, sizeof(pars));
	dijkstra(0);
}