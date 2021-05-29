#include <iostream>
#include <utility>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct Node {
	int i;
	int e1, e2;
	Node() {}
	Node(int i, int e1, int e2) {
		this->i = i;
		this->e1 = e1;
		this->e2 = e2;
	}
};

int N;
pair<int, int> nc[100000];
int comps[200000];
int link[200000];
int compsize[200000];
vector<pair<int, int>> edges;
vector<Node> nodes;

int findrep(int i) {
	while (link[i] != i) i = link[i];
	return i;
}

bool samecomp(int a, int b) {
	return findrep(a) == findrep(b);
}

void unite(int a, int b) {
	a = findrep(a); b = findrep(b);
	if (a < b) swap(a, b);
	compsize[a] += compsize[b];
	link[b] = a;
}

void findComp(int root, int comp) {
	queue<int> inComp;
	inComp.push(root);
	while (!inComp.empty()) {
		int i = inComp.front();
		Node node = nodes[inComp.front()];
		inComp.pop();

		int e1 = node.e1, e2 = node.e2;
		if (!comps[e1]) {
			comps[e1] = comp;
			unite(i, e1);
			inComp.push(e1);
		}
		if (!comps[e2]) {
			comps[e2] = comp;
			unite(i, e2);
			inComp.push(e2);
		}
	}
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);

	cin >> N;
	edges.resize(N * 2, { -1, -1 });
	for (int i = 0; i < N; i++) {
		int c, e1, e2, e3, e4;
		cin >> c >> e1 >> e2 >> e3 >> e4;
		e1--; e2--; e3--; e4--;
		nc[i] = { c, i };

		int ni = nodes.size();
		if (edges[e1].first != -1) edges[e1].second = ni;
		else edges[e1].first = ni;
		if (edges[e2].first != -1) edges[e2].second = ni;
		else edges[e2].first = ni;
		nodes.push_back(Node(i, e1, e2));

		ni = nodes.size();
		if (edges[e3].first != -1) edges[e3].second = ni;
		else edges[e3].first = ni;
		if (edges[e4].first != -1) edges[e4].second = ni;
		else edges[e4].first = ni;
		nodes.push_back(Node(i, e3, e4));
	}
	for (int i = 0; i < nodes.size(); i++) {
		int e1 = nodes[i].e1, e2 = nodes[i].e2;
		int ni = edges[e1].first == i ? edges[e1].second : edges[e1].first;
		nodes[i].e1 = ni;
		ni = edges[e2].first == i ? edges[e2].second : edges[e2].first;
		nodes[i].e2 = ni;
	}

	for (int i = 0; i < nodes.size(); i++) {
		link[i] = i;
		compsize[i] = 1;
	}
	int comp = 1;
	for (int i = 0; i < nodes.size(); i++) {
		if (!comps[i]) findComp(i, comp++);
	}

	sort(nc, nc + N);
	long long cost = 0;
	for (int i = 0; i < N; i++) {
		int n1 = nc[i].second * 2;
		int n2 = n1 + 1;
		if (!samecomp(n1, n2)) {
			cost += nc[i].first;
			unite(n1, n2);
		}
	}
	cout << cost << '\n';
}