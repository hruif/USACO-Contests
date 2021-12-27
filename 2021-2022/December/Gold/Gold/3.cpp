#include <iostream>
#include <vector>
#include <set>
#include <map>

using namespace std;

int T;
vector<vector<int>> c;
vector<set<int>> outside_of, has_inside, is_before;

void clear_all() {
	c.clear();
	outside_of.clear();
	has_inside.clear();
	is_before.clear();
}

void resize_all(int N, int M) {
	c.resize(M);
	outside_of.resize(N);
	has_inside.resize(N);
	is_before.resize(N);
}

int main() {
	cin >> T;
	while (T--) {
		clear_all();

		int N, M;
		cin >> N >> M;
		resize_all(N, M);
		for (int i = 0; i < M; i++) {
			int k;
			cin >> k;
			c[i].resize(k);
			for (int j = 0; j < k; j++) cin >> c[i][j];
			for (int j = 0; j < k; j++) c[i][j]--;
		}
		vector<int> last_seen(N, -1);
		bool valid = true;
		for (int i = 0; i < M; i++) {
			int k = c[i].size();
			for (int j = 0; j < k; j++) {
				int cur = c[i][j];
				if (last_seen[cur] != -1 && i - last_seen[cur] > 1) 
					valid = false;
				last_seen[cur] = i;
			}
		}
		for (int i = 0; i < M; i++) {
			int k = c[i].size();
			set<int> seen;
			for (int j = 0; j < k; j++) {
				int cur = c[i][j];
				if (seen.find(cur) == seen.end()) {
					seen.insert(cur);
					int l = j + 1;
					for (; c[i][l] != cur; l++) {
						if (outside_of[c[i][l]].find(cur) != outside_of[c[i][l]].end()) 
							valid = false;
						outside_of[cur].insert(c[i][l]);
						has_inside[cur].insert(c[i][l]);
					}
					map<int, int> cnts;
					for (; l < k; l++) {
						cnts[c[i][l]]++;
					}
					for (auto x : cnts) {
						if (x.second == 2) {
							if (is_before[x.first].find(cur) != is_before[x.first].end())
								valid = false;
							if (has_inside[x.first].find(cur) != has_inside[x.first].end())
								valid = false;
							if (has_inside[cur].find(x.first) != has_inside[cur].end())
								valid = false;
							is_before[cur].insert(x.first);
							outside_of[x.first].insert(cur);
							outside_of[cur].insert(x.first);
						}
					}
				}
			}
			for (auto x : seen) {
				for (int j = 0; j < N; j++) {
					if (seen.find(j) == seen.end()) {
						if (has_inside[j].find(x) != has_inside[j].end())
							valid = false;
						outside_of[x].insert(j);
					}
				}
			}
		}
		if (valid) cout << "YES\n";
		else cout << "NO\n";
	}
}