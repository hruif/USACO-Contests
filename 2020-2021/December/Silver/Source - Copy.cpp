#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_set>

using namespace std;

int N;
vector<unordered_set<int>> connected;

int dfs(int c) {
	int size = connected[c].size();
	int ds = 0;
	int cs = 1;
	while (cs <= size) {
		cs *= 2;
		ds++;
	}
	int total = ds;
	for (auto i : connected[c]) {
		int nc = i;
		connected[i].erase(connected[i].find(c));
		total += dfs(nc) + 1;
	}
	return total;
}

int main() {
	cin >> N;
	connected.resize(N);
	for (int i = 0; i < N - 1; i++) {
		int a, b;
		cin >> a >> b;
		a--, b--;
		connected[a].insert(b);
		connected[b].insert(a);
	}
	int days = dfs(0);

	cout << days << '\n';
}