#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

int N, M;
int removed[3000];
bool tbov[3000];
bool bov[3000];
vector<vector<int>> connected;

bool isconnected() {
	queue<int> v;
	int uv = 0;
	for (int i = 0; i < N; i++) {
		uv = i;
		if (!bov[i]) break;
	}

	v.push(uv);
	while (!v.empty()) {
		int b = v.front();
		v.pop();

		if (bov[b]) continue;
		bov[b] = true;

		for (int i = 0; i < connected[b].size(); i++) {
			int& nb = connected[b][i];
			if (!bov[nb]) {
				v.push(nb);
			}
		}
	}

	for (int i = 0; i < N; i++) {
		if (!bov[i]) return false;
	}
	return true;
}

int main() {
	ifstream fin("closing.in");
	ofstream fout("closing.out");

	fin >> N >> M;
	connected.resize(N);
	for (int i = 0; i < M; i++) {
		int b1, b2;
		fin >> b1 >> b2;
		b1--, b2--;

		connected[b1].push_back(b2);
		connected[b2].push_back(b1);
	}

	for (int i = 0; i < N; i++) {
		int r;
		fin >> r;
		removed[i] = r - 1;
	}

	for (int i = 0; i < N; i++) {
		tbov[i] = bov[i];
	}
	if (isconnected()) fout << "YES\n";
	else fout << "NO\n";
	for (int i = 0; i < N; i++) {
		bov[i] = tbov[i];
	}
	for (int i = 0; i < N - 1; i++) {
		int& r = removed[i];
		bov[r] = true;

		for (int i = 0; i < N; i++) {
			tbov[i] = bov[i];
		}
		if (isconnected()) fout << "YES\n";
		else fout << "NO\n";
		for (int i = 0; i < N; i++) {
			bov[i] = tbov[i];
		}
	}
}