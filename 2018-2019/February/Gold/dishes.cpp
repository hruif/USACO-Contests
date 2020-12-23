#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

int N;
vector<vector<int>> stacks;

int main() {
	ifstream fin("dishes.in");
	ofstream fout("dishes.out");

	fin >> N;
	int maxplace = 0;
	int ans = 0;
	for (int i = 0; i < N; i++) {
		int d;
		fin >> d;
		if (d < maxplace && ans == 0) ans = i;
		int p = 0;
		while (p < stacks.size() && d > stacks[p][0]) {
			p++;
		}
		if (p == stacks.size()) stacks.push_back(vector<int>(1, d));
		else {
			if (stacks[p][stacks[p].size() - 1] < d) {
				while (stacks[p][stacks[p].size() - 1] < d) {
					maxplace = stacks[p][stacks[p].size() - 1];
					stacks[p].erase(stacks[p].end() - 1);
				}
				stacks[p].push_back(d);
				for (int i = 0; i < p; i++) {
					stacks.erase(stacks.begin());
				}
			}
			else {
				stacks[p].push_back(d);
			}
		}
	}
	fout << ans << '\n';
}