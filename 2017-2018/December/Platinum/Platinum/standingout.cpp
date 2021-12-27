#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <fstream>

using namespace std;

ifstream fin("standingout.in");
ofstream fout("standingout.out");

int N;
string s;
vector<pair<int, int>> a;

void compress(vector<int>& V, vector<int>& C) {
	copy(V.begin(), V.end(), C.begin());
	sort(C.begin(), C.end());
	auto cend = unique(C.begin(), C.end());
	for (int i = 0; i < N; i++) {
		V[i] = lower_bound(C.begin(), cend, V[i]) - C.begin() + 1;
	}
	V.push_back(0); C.push_back(0);
}

vector<int> compute_sa(const string& s) {
	int n = s.size();
	const int alphabet = 256;

	vector<int> pos(n, n), cl(n);
	vector<int> cnts(max(alphabet, n), 0);
	for (int i = 0; i < n; i++)
		cnts[s[i]]++;
	for (int i = 1; i < alphabet; i++)
		cnts[i] += cnts[i - 1];
	for (int i = 0; i < n; i++)
		pos[--cnts[s[i]]] = i;
	cl[0] = 0;
	int classes = 0;
	for (int i = 1; i < n; i++) {
		if (s[pos[i]] != s[pos[i - 1]]) classes++;
		cl[pos[i]] = classes;
	}
	classes++;
	//cl.push_back(0);
	//cnts.push_back(0);
	//n++;

	vector<int> pn(n), cn(n);
	for (int h = 0; (1 << h) < n; h++) {
		int k = (1 << h);
		for (int i = 0; i < n; i++) {
			pn[i] = pos[i] - k;
			if (pn[i] < 0) pn[i] += n;
		}
		fill(cnts.begin(), cnts.end(), 0);
		for (int i = 0; i < n; i++) 
			cnts[cl[pn[i]]]++;
		for (int i = 1; i < classes; i++)
			cnts[i] += cnts[i - 1];
		for (int i = n - 1; i >= 0; i--)
			pos[--cnts[cl[pn[i]]]] = pn[i];
		cn[pos[0]] = 0;
		classes = 0;
		for (int i = 1; i < n; i++) {
			if (cl[pos[i]] != cl[pos[i - 1]] || cl[(pos[i] + k) % (n)] != cl[(pos[i - 1] + k) % (n)]) classes++;
			cn[pos[i]] = classes;
		}
		classes++;
		cl.swap(cn);
	}
	return pos;
}

vector<int> compute_lcp(const string& s, const vector<int>& sa) {
	int n = s.size() - 1;
	vector<int> lcp(n);
	vector<int> rank(n + 1);
	for (int i = 0; i <= n; i++) rank[sa[i]] = i;

	int len = 0;
	for (int i = 0; i < n; i++) {
		int sai = rank[i]; // index in sa
		int j = sa[sai - 1];
		int tlen = len;
		while (i + len < n && j + len < n && s[i + len] == s[j + len]) len++;
		/*if (sai < n) {
			int k = sa[sai + 1];
			while (i + tlen < n && k + tlen < n && s[i + tlen] == s[k + tlen]) tlen++;
			len = max(len, tlen);
		}*/
		lcp[sai - 1] = len;
		if (len) len--;
	}
	lcp.push_back(0);
	return lcp;
}

int main() {
	fin >> N;
	for (int i = 0; i < N; i++) {
		string cur;
		fin >> cur;
		s += cur + "$";
		for (int j = 0; j < cur.size(); j++) 
			a.push_back({ i, cur.size() - j });
		a.push_back({ -1, -1 }); // account for $s
	}
	s.push_back(0); // make it easier to compute lcp
	a.push_back({ -1, -1 }); // account for 0 at end
	vector<int> sa = compute_sa(s);
	vector<int> lcp = compute_lcp(s, sa);
	vector<int> ans(N);
	int n = s.size() - 1;
	for (int i = 1; i <= n; i++) {
		int j = sa[i];
		int ind = a[j].first;
		if (ind == -1) continue;
		int sz = 1;
		while (i + sz <= n && a[sa[i + sz]].first == ind)
			sz++;

		int len = lcp[i - 1];
		for (int j = i; j < i + sz; j++) {
			ans[ind] += max(a[sa[j]].second - max(len, lcp[j]), 0);
			len = min(len, lcp[j]);
		}
		i += sz - 1;
	}
	for (auto x : ans) fout << x << '\n';
}