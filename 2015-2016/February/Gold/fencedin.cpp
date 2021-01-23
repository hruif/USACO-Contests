#include <iostream>
#include <fstream>
#include <utility>
#include <queue>
#include <algorithm>
#include <list>

#define ll long long

using namespace std;

struct Edge {
	int a, b;
	ll d;
	Edge() {}
	Edge(int a, int b, ll d) {
		this->a = a;
		this->b = b;
		this->d = d;
	}

	bool operator<(const Edge a) const {
		return d < a.d;
	}
};

ll A, B;
int n, m;
int a[2002], b[2002];
int link[4100000], usize[4100000];
Edge edges[4100000 * 2];

int find(int x) {
	while (x != link[x]) x = link[x];
	return x;
}

bool same(int a, int b) {
	return find(a) == find(b);
}

void unite(int a, int b) {
	a = find(a);
	b = find(b);
	if (usize[a] < usize[b]) swap(a, b);
	usize[a] += usize[b];
	link[b] = a;
}

int main() {
	ifstream fin("fencedin.in");
	ofstream fout("fencedin.out");

	fin >> A >> B >> n >> m;
	a[0] = 0, b[0] = 0;
	for (int i = 1; i <= n; i++) fin >> a[i];
	for (int i = 1; i <= m; i++) fin >> b[i];
	a[n + 1] = A, b[m + 1] = B;
	sort(a, a + n + 2);
	sort(b, b + m + 2);

	for (int i = 0; i < (n + 1) * (m + 1); i++) link[i] = i;
	for (int i = 0; i < (n + 1) * (m + 1); i++) usize[i] = 1;

	int es = 0;
	for (int i = 0; i < (n + 1) * (m + 1); i++) {
		if (i % (m + 1) < m) edges[es++] = Edge(i, i + 1, a[i / (m + 1) + 1] - a[i / (m + 1)]);
		if (i / (m + 1) < n) edges[es++] = Edge(i, i + (m + 1), b[i % (m + 1) + 1] - b[i % (m + 1)]);
	}
	sort(edges, edges + es);

	ll dist = 0;
	for (int i = 0; i < es; i++) {
		if (!same(edges[i].a, edges[i].b)) {
			dist += edges[i].d;
			unite(edges[i].a, edges[i].b);
		}
	}

	fout << dist << '\n';
}