#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <string>

#define ll long long

using namespace std;

int N;
bool isfile[100000];
int pars[100000];
vector<vector<pair<int, int>>> paths;
pair<ll, int> sts[2][100000];

pair<ll, int> setstf(int node, int par) {
	pars[node] = par;
	int size = 0;
	pair<ll, int> st(0, isfile[node] ? 1 : 0);
	for (int i = 0; i < paths[node].size(); i++) {
		int next = paths[node][i].first;
		if (next == par) continue;
		pair<ll, int> nst = setstf(next, node);
		st.first += nst.first + nst.second * paths[node][i].second;
		st.second += nst.second;
	}
	sts[0][node] = st;
	return st;
}

void setstb(int node, int par, pair<ll, int> parb) {
	pair<ll, int> st(parb.first + parb.second * 3, parb.second);
	sts[1][node] = st;
	st.first += sts[0][node].first, st.second += sts[0][node].second;
	for (int i = 0; i < paths[node].size(); i++) {
		int next = paths[node][i].first;
		if (next == par) continue;
		pair<ll, int> nst = sts[0][next];
		st.first -= nst.first + nst.second * paths[node][i].second;
		st.second -= nst.second;
		setstb(next, node, st);
		st.first += nst.first + nst.second * paths[node][i].second;
		st.second += nst.second;
	}
}

int ss[100000];

int main() {
	ifstream fin("dirtraverse.in");
	ofstream fout("dirtraverse.out");

	fin >> N;
	paths.resize(N);
	vector<vector<int>> parents(N);
	for (int i = 0; i < N; i++) {
		string s;
		int m;
		fin >> s >> m;
		ss[i] = s.size();
		if (m == 0) isfile[i] = true;
		for (int j = 0; j < m; j++) {
			int f;
			fin >> f;
			f--;
			parents[f].push_back(i);
			paths[f].push_back(make_pair(i, 3));
		}
	}
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < parents[i].size(); j++) {
			paths[parents[i][j]].push_back(make_pair(i, ss[i] + 1));
		}
	}
	setstf(0, -1);
	pair<ll, int> stb = sts[0][0];
	for (int i = 0; i < paths[0].size(); i++) {
		pair<ll, int> nst = sts[0][paths[0][i].first];
		stb.first -= nst.first + nst.second * paths[0][i].second;
		stb.second -= nst.second;
		setstb(paths[0][i].first, 0, stb);
		stb.first += nst.first + nst.second * paths[0][i].second;
		stb.second += nst.second;
	}
	ll minpath = (ll)(1e16);
	for (int i = 0; i < N; i++) {
		if (isfile[i]) continue;
		ll path = sts[0][i].first + sts[1][i].first - sts[0][i].second - sts[1][i].second;
		minpath = min(minpath, path);
	}
	fout << minpath << '\n';
}