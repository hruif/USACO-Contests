#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <string.h>
#include <unordered_set>
#include <algorithm>

using namespace std;

int N, K;
vector<vector<string>> adjs;
vector<unordered_set<string>> adjsset;
vector<vector<string>> nohave;
vector<string> ans;

bool findFirst(int adj) {
	if (adj == adjs.size()) {
		for (int j = 0; j < N; j++) {
			bool no = true;
			for (int i = 0; i < ans.size(); i++) {
				if (ans[i] != nohave[j][i]) {
					no = false;
					break;
				}
			}
			if (no) {
				return false;
			}
		}
		return true;
	}
	ans.resize(adj + 1);
	for (int i = 0; i < adjs[adj].size(); i++) {
		ans[adj] = adjs[adj][i];
		if (findFirst(adj + 1)) {
			return true;
		}
	}
	return false;
}

int main() {
	ifstream fin("nocow.in");
	fin >> N >> K;
	string farmer, john, has, no;
	fin >> farmer >> john >> has >> no;
	int numOfAdjectives = 0;
	string adj;
	fin >> adj;
	nohave.emplace_back();
	while (adj != "cow.") {
		nohave[0].push_back(adj);
		adjs.emplace_back();
		adjs[numOfAdjectives].push_back(adj);
		adjsset.emplace_back();
		adjsset[numOfAdjectives].insert(adj);
		numOfAdjectives++;
		fin >> adj;
	}
	for (int i = 1; i < N; i++) {
		fin >> farmer >> john >> has >> no;
		nohave.emplace_back();
		for (int j = 0; j < numOfAdjectives; j++) {
			fin >> adj;
			nohave[i].push_back(adj);
			if (adjsset[j].find(adj) == adjsset[j].end()) {
				adjsset[j].insert(adj);
				adjs[j].push_back(adj);
			}
		}
		fin >> adj;
	}
	for (int i = 0; i < numOfAdjectives; i++) {
		sort(adjs[i].begin(), adjs[i].end());
	}

	long long total = 1;
	for (int i = 0; i < numOfAdjectives; i++) {
		total *= adjs[i].size();
	}
	bool counted[100];
	memset(counted, false, sizeof(counted));

	int subs[100];
	memset(subs, 0, sizeof(subs));
	if (K > 1) {
		for (int i = 0; i < numOfAdjectives; i++) {
			total /= adjs[i].size();
			int p = 0;
			while (K >= total) {
				K -= total;
				subs[i] += total;
				bool lg = false;
				for (int j = 0; j < N; j++) {
					if (counted[j]) {
						continue;
					}
					bool big = false;
					for (int k = 0; k < i; k++) {
						if (ans[k] < nohave[j][k]) {
							counted[j] = true;
							K++;
							break;
						}
						if (ans[k] > nohave[j][k]) {
							big = true;
							break;
						}
					}
					if (big) {
						continue;
					}
					if (nohave[j][i] <= adjs[i][p] && !counted[j]) {
						counted[j] = true;
						K++;
					}
				}
				p++;
			}
			if (p >= adjs[i].size()) {
				total *= adjs[i].size();
				total *= adjs[i - 1].size();
				i -= 2;
				p = 0;
				K += subs[i] + subs[i + 1];
				subs[i + 1] = 0;
				subs[i + 2] = 0;
			}
			else {
				ans.push_back(adjs[i][p]);
			}
		}
	}
	else {
		findFirst(0);
	}
	ofstream fout("nocow.out");
	for (int i = 0; i < numOfAdjectives; i++) {
		if (i != 0) {
			fout << ' ';
		}
		fout << ans[i];
	}
	fout << '\n';
}