#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

string s;
vector<int> inds[26];
vector<int> psums[26];

int main() {
	cin >> s;
	int ss = s.size();
	int maxocc = 0;
	for (int i = 0; i < 26; i++) inds[i].push_back(-1);
	for (int i = 0; i < ss; i++) {
		inds[s[i] - 'a'].push_back(i);
	}
	vector<int> occ(26, 0);
	for (int i = 0; i < ss; i++) {
		occ[s[i] - 'a']++;
		for (int j = 0; j < 26; j++) {
			psums[j].push_back(occ[j]);
		}
	}
	int maxval = 0;
	for (int i = 0; i < 26; i++) {
		int i1 = inds[i][0];
		int val = 0;
		int maxdupe = 0;
		for (int j = 1; j < inds[i].size(); j++) {
			val++;
			int i2 = inds[i][j];
			if (i1 == i2 - 1) {
				i1 = i2;
				continue;
			}
			for (int k = 0; k < 26; k++) {
				int dupe = psums[k][i2 - 1] - psums[k][i1 + 1] - 1;
				if (dupe > 0) {
					int as = 5;
				}
				maxdupe = max(maxdupe, dupe);
			}
			i1 = i2;
		}
		maxval = max(maxval, val + maxdupe);
	}
	cout << maxval << '\n';
}