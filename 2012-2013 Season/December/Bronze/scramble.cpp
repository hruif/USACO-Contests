#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <utility>

using namespace std;

int N;
string n[50000]; // names
string sn[50000]; //sorted names
string srn[50000]; // sorted reversed names
unordered_map<string, pair<int, int>> minmaxes;
unordered_map<string, int> spos;

int main() {
	ifstream fin("input.in");
	fin >> N;
	for (int i = 0; i < N; i++) {
		fin >> n[i];
		sn[i] = n[i];
		srn[i] = sn[i];
		sort(sn[i].begin(), sn[i].end());
		srn[i] = sn[i];
		for (int j = 0; j < sn[i].size(); j++) {
			srn[i][sn[i].size() - j - 1] = sn[i][j];
		}
	}
	sort(sn, sn + N);
	sort(srn, srn + N);
	int snp = 0;
	int srnp = 0;
	for (int i = 0; i < N; i++) {
		spos[sn[i]] = i;
		while (sn[i] > srn[srnp]) {
			srnp++;
		}
		minmaxes[sn[i]].first = srnp;
	}
	for (int i = 0; i < N; i++) {
		while (srn[i] > sn[snp] && snp < N) {
			snp++;
		}
		int max = snp;
		string s = srn[i];
		sort(s.begin(), s.end());
		if (spos[s] < max) {
			max--;
		}
		minmaxes[s].second = max;
	}
	ofstream fout("output.out");
	for (int i = 0; i < N; i++) {
		string s = n[i];
		sort(s.begin(), s.end());
		fout << minmaxes[s].first + 1 << ' ' << minmaxes[s].second + 1 << '\n';
	}
}