#include <iostream>
#include <vector>
#include <set>
#include <map>

using namespace std;

int T;
vector<vector<int>> beams;
vector<set<int>> has_inside;
vector<set<int>> afters;
vector<set<int>> separate;

int main() {
	cin >> T;
	while (T--) {
		beams.clear(); has_inside.clear(); afters.clear(); separate.clear();

		int N, M;
		cin >> N >> M;
		has_inside.resize(N);
		afters.resize(N);
		separate.resize(N);
		vector<int> lasts(N, -1);
		for (int i = 0; i < M; i++) {
			int k;
			cin >> k;
			vector<int> beam(k);
			for (int j = 0; j < k; j++) cin >> beam[j];
			for (int j = 0; j < k; j++) beam[j]--;
			beams.push_back(beam);
		}
		/*bool val = true;
		for (int i = 0; i < M; i++) {

		}*/

		bool val = true;
		for (int i = 0; i < M; i++) {
			set<int> colors;
			int k = beams[i].size();
			for (int j = 0; j < k; j++) {
				int c = beams[i][j];

				if (lasts[c] != -1 && lasts[c] < i - 1) val = false;
				else lasts[c] = i;

				if (colors.find(c) == colors.end()) { // initial
					colors.insert(c);
					map<int, int> checks;
					for (int l = 0; l < j; l++) checks[beams[i][l]]++;
					int r = 0;
					for (int l = j + 1; l < k; l++) {
						if (beams[i][l] == c) {
							r = l;
							break;
						}
					}
					for (int l = r + 1; l < k; l++) {
						if (checks[beams[i][l]] == 0) {
							separate[c].insert(beams[i][l]);
							separate[beams[i][l]].insert(c);
							checks[beams[i][l]]++;
						}
						else if (checks[beams[i][l]] == 2) {
							if (has_inside[beams[i][l]].find(c) != has_inside[beams[i][l]].end()) val = false;
						}
						checks[beams[i][l]]++;
						if (afters[beams[i][l]].find(c) != afters[beams[i][l]].end()) val = false;
						if (has_inside[c].find(beams[i][l]) != has_inside[c].end()) val = false;
						afters[c].insert(beams[i][l]);
					}
					for (auto x : checks) if (x.second < 2) val = false;
					for (int l = j + 1; l < r; l++) {
						if (has_inside[beams[i][l]].find(c) != has_inside[beams[i][l]].end()) val = false;
						if (separate[beams[i][l]].find(c) != separate[beams[i][l]].end()) val = false;
						if (afters[c].find(beams[i][l]) != afters[c].end()) val = false;
						has_inside[c].insert(beams[i][l]);
					}
				}
				else {

				}
			}
			for (auto x : colors) {
				for (int j = 0; j < N; j++) {
					if (colors.find(j) == colors.end()) {
						if (has_inside[j].find(x) != has_inside[j].end()) val = false;
						separate[x].insert(j);
					}
				}
			}
		}

		cout << (val ? "YES\n" : "NO\n");
	}
}