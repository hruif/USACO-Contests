#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
#include <map>
#include <cstdlib>
#include <cmath>
#include <functional>
#include <cstring>
#include <algorithm>
#include <string.h>

#define pii pair<int, int>

using namespace std;

int N, M, K;
int markets[5];
int inf = 1000000000;
vector<pii> graph[10005];
int shortest[5][10005];
bool isMark[10005];

void dijkstra(int start) {
	priority_queue <pii, vector<pii>, greater<pii>> pq;
	pq.push(pii(0, markets[start]));

	while (!pq.empty()) {
		int curdist = pq.top().first;
		int curnode = pq.top().second;
		pq.pop();

		if (shortest[start][curnode] <= curdist) {
			continue;
		}

		shortest[start][curnode] = curdist;

		for (int i = 0; i < graph[curnode].size(); i++) {
			int nextnode = graph[curnode][i].second;
			int nextdist = graph[curnode][i].first + curdist;

			if (nextdist < shortest[start][nextnode]) {
				pq.push(pii(nextdist, nextnode));
			}
		}
	}
} // above is all copied from solution page

int main() {
	ifstream fin("relocate.in");
	ofstream fout("relocate.out");
	fin >> N >> M >> K;
	for (int i = 0; i < K; i++) {
		fin >> markets[i];
		markets[i]--;
		isMark[markets[i]] = true;
	}
	for (int i = 0; i < M; i++) {
		int a, b, l;
		fin >> a >> b >> l;
		a--;
		b--;
		graph[a].push_back(pii(l, b));
		graph[b].push_back(pii(l, a));
	}
	for (int i = 0; i < K; i++) {
		memset(shortest[i], inf, sizeof(shortest[i]));
		dijkstra(i);
	}
	int min = -1;
	for (int i = 
}