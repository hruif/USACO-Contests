#include <iostream>
#include <fstream>
#include <vector>
#include <string.h>
#include <queue>

#define MAX_N 100005

using namespace std;

int N, Q;
int ites[MAX_N]; // intital tree's entertainment vals

vector<int> con[MAX_N];

int ips[MAX_N]; // initial parents
vector<int> ichs[MAX_N]; // initial children
int iszs[MAX_N]; // initial subtree sizes
int itd[MAX_N]; // initial tree depths

int itof[MAX_N]; // convert initial index to final tree index

int e[MAX_N]; // final tree's entertainment vals;
int td[MAX_N]; // final tree depths
vector<int> ch[MAX_N]; // children in final tree

int inh[MAX_N]; // in which heavy path
int hbs[MAX_N][2]; // heavy path start and end
int n2pd[MAX_N][20]; // node 2^d layers above current
vector<int> segtrees[MAX_N]; // segment trees of heavy paths

void checkout(int i) {
	if (i < 0) {
		ofstream fout("cowland.out");
		fout << "BAD INDEX";
		exit(0);
	}
}

int cntt = 0;

int buildtree(int ind, int parent) {
	cntt++;
	int size = 1;
	ips[ind] = parent;
	int coninds = con[ind].size();
	for (int i = 0; i < coninds; i++) {
		int next = con[ind][i];
		if (next == parent) continue;

		ichs[ind].push_back(next);
		size += buildtree(next, ind);
	}
	iszs[ind] = size;
	cntt--;
	return size;
}

/*
struct node {
	int ind, p;
	node() {}
	node (int ind, int p) { ind(ind), p(p); }
};
queue<node> addtree;
int buildtree() {
	ips[1] = -1;
	addtree.insert(node(1, -1));
	while (!addtree.empty()) {
		node n = addtree.front();
		addtree.pop();
		for (int i = 0; i < con[n.ind].size(); i++) {
			
		}
	}
}
*/

int fis = 0;
int his = 0;
void findHL(int itind, int d) { // finding heavy-light branches - given initial tree index
	int maxtree = 0, maxtreeind = -1;
	itd[itind] = d;
	inh[fis] = his; // current index in heavy branch hi
	hbs[his][1] = itind; // set end of heavy branch to initial index - will convert later
	itof[itind] = fis++; // initial index maps to current index

	for (int i = 0; i < ichs[itind].size(); i++) { // find largest subtree
		int chi = ichs[itind][i]; // child index
		if (iszs[chi] > maxtree) {
			maxtree = iszs[chi];
			maxtreeind = chi;
		}
	}

	if (maxtreeind == -1) return; // if root node, return

	findHL(maxtreeind, d + 1); // continue heavy branch
	for (int i = 0; i < ichs[itind].size(); i++) {
		int chi = ichs[itind][i]; // child index
		if (chi == maxtreeind) continue; // dont go down heavy branch
		his++; // start new heavy branch
		hbs[his][0] = chi;
		findHL(chi, d + 1);
	}
}

int segTXOR(int hi, int p) { // return xor of segment
	int curval = segtrees[hi][p];
	if (curval == -1) {
		curval = segTXOR(hi, p * 2) ^ segTXOR(hi, p * 2 + 1);
		segtrees[hi][p] = curval;
	}
	return curval;
}

void setSegTree(int hi) { // set segment tree for heavy branch
	int first = hbs[hi][0], last = hbs[hi][1];
	int hbsize = last - first + 1;
	int n = 1;
	while (n < hbsize) n *= 2; // segment tree needs n as power of 2
	segtrees[hi].resize(n * 2, -1);

	for (int i = 0; i < n; i++) { // set initial vals in segment tree
		if (i + first > last) segtrees[hi][i + n] = 0;
		else segtrees[hi][i + n] = e[i + first];
	}
	if (n > 1) segtrees[hi][1] = segTXOR(hi, 2) ^ segTXOR(hi, 3);
}

void updTree(int t, int k, int newVal) { // update segment trees when changing value
	k += segtrees[t].size() / 2;
	segtrees[t][k] = newVal;
	for (k /= 2; k >= 1; k /= 2) {
		segtrees[t][k] = segtrees[t][2 * k] ^ segtrees[t][2 * k + 1];
	}
}

void setAncestors(int node) {
	int anc = 2;
	int d = 1;
	while (anc <= td[node]) {
		n2pd[node][d] = n2pd[n2pd[node][d - 1]][d - 1];
		anc *= 2;
		d++;
	}
}

int moveSameLayer(int a, int l2) { // move a to layer l2
	checkout(a);
	while (td[a] != l2) {
		int d = 0;
		while (n2pd[a][d] >= 0 && td[n2pd[a][d]] >= l2) d++; // find ancestor by powers of 2
		d--;
		checkout(d);
		a = n2pd[a][d];
	}
	return a;
}

int findLCA(int a, int b) { // find lowest common ancestor
	if (td[a] > td[b]) a = moveSameLayer(a, td[b]); //move a and b to same layer
	else if (td[b] > td[a]) b = moveSameLayer(b, td[a]);

	while (a != b) {
		int a2 = n2pd[a][0], b2 = n2pd[b][0];
		if (a2 == b2) {
			a = a2;
			b = b2;
			break;
		}
		int d = 1;
		while (n2pd[a][d] >= 0 && n2pd[a][d] != n2pd[b][d]) d++;
		d--;
		a = n2pd[a][d];
		b = n2pd[b][d];
	}
	return a;
}

int segXOR(int hi, int p) {
	int l = segtrees[hi].size() / 2;
	p -= hbs[hi][0];
	p += segtrees[hi].size() / 2;
	int s = 0;
	while (l <= p) {
		if (l % 2 == 1) s ^= segtrees[hi][l++];
		if (p % 2 == 0) s ^= segtrees[hi][p--];
		l /= 2;
		p /= 2;
	}
	return s;
}

int findEnjoy(int a, int b) {
	int lca = findLCA(a, b);
	int aXOR = 0;
	while (inh[a] != inh[lca]) {
		aXOR ^= segXOR(inh[a], a);
		a = n2pd[hbs[inh[a]][0]][0];
	}
	aXOR ^= segXOR(inh[a], a);
	while (inh[b] != inh[lca]) {
		aXOR ^= segXOR(inh[b], b);
		b = n2pd[hbs[inh[b]][0]][0];
	}
	aXOR ^= segXOR(inh[b], b);
	return aXOR ^ e[lca];
}

int main() {
	ifstream fin("cowland.in");
	ofstream fout("cowland.out");

	fin >> N >> Q;
	for (int i = 0; i < N; i++) {
		fin >> ites[i];
	}
	for (int i = 0; i < N - 1; i++) {
		int a, b;
		fin >> a >> b;
		con[a].push_back(b);
		con[b].push_back(a);
	}

	int tsize = buildtree(1, -1);
	if (tsize != N) {
		cout << "SOMETHING'S WRONG WITH BUILDTREE!" << endl;
		return 0;
	}

	memset(inh, -1, sizeof(inh)); // no nodes in any heavy branch
	memset(n2pd, -1, sizeof(n2pd)); // no ancestors
	hbs[0][0] = 0; // set first node start of first heavy branch
	findHL(1, 0);
	his++;

	for (int i = 0; i < N; i++) { // change from intial tree to final tree
		e[itof[i + 1]] = ites[i];
		td[itof[i + 1]] = itd[i + 1];
		n2pd[itof[i + 1]][0] = i > 0 ? itof[ips[i + 1]] : -1;
		for (int j = 0; j < ichs[i + 1].size(); j++) {
			int chi = ichs[i + 1][j];
			ch[itof[i + 1]].push_back(itof[chi]);
		}
	}
	for (int i = 0; i < his; i++) {
		hbs[i][0] = itof[hbs[i][0]];
		hbs[i][1] = itof[hbs[i][1]];
	}

	for (int i = 0; i < N; i++) {
		setAncestors(i);
	}
	for (int i = 0; i < his; i++) {
		setSegTree(i);
	}
	
	for (int q = 0; q < Q; q++) {
		int a, i, b;
		fin >> a >> i >> b;
		if (a == 1) {
			int ind = itof[i];
			e[ind] = b;
			int t = inh[ind];
			updTree(t, ind - hbs[t][0], b);
		}
		else {
			fout << findEnjoy(itof[i], itof[b]) << '\n';
		}
	}
}