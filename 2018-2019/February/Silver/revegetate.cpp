#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <string.h>

using namespace std;

int N, M;
int val[100000];
vector<int> rel[100000];
bool gd[100000];

int main() {
	ifstream fin("revegetate.in");
	ofstream fout("revegetate.out");

	memset(val, -1, sizeof(val));

	bool impossible = false;
	fin >> N >> M;
	for (int i = 0; i < M; i++) {
		char d;
		int a, b;
		fin >> d >> a >> b;
		a--, b--;`
		if (d == 'S'
		rel[a].push_back(b);
		rel[b].push_back(a);
	}

	int gs = 0;
	for (int i = 0; i < N; i++) {
		if (gd[i]) continue;

		gs++;
		queue<int> c;
		c.push(i);
		while (!c.empty()) {
			int p = c.front();
			c.pop();
			if (gd[p]) continue;
			gd[p] = true;
			for (int j = 0; j < rel[p].size(); j++) {
				if (!gd[rel[p][j]]) c.push(rel[p][j]);
			}
		}
	}

	cout << 1;
	for (int i = 0; i < gs; i++) cout << 0;
	cout << '\n';
}