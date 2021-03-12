#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <utility>

#define ll long long
#define pii pair<int, int>

using namespace std;

int N, K;
int inds[100000], line[100000]; // index for each value in line, values in line
int indmove[100000]; // how much value at index i moves
vector<pii> ps;
ll M;

bool visited[100000];
void checkgroup(int par) {
	vector<int> ingroup;
	ingroup.push_back(par);
}

int main() {
	cin >> N >> K >> M;
	for (int i = 0; i < N; i++) line[i] = i;
	for (int i = 0; i < N; i++) inds[i] = i;
	for (int i = 0; i < K; i++) {
		pii p;
		cin >> p.first >> p.second;
		p.first--, p.second--;
		int a = p.first, b = p.second;
		int av = line[a], bv = line[b];
		line[a] = bv; line[b] = av;
		inds[av] = b; inds[bv] = a;
		ps.push_back(p);
	}

	for (int i = 0; i < N; i++) {
		checkgroup(par);
	}
}