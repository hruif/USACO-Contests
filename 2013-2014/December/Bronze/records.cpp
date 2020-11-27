#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <unordered_map>

using namespace std;

int N;
unordered_map<string, int> cowind;
unordered_map<int, int> occur;

int main() {
	ifstream fin("records.in");
	fin >> N;
	int ind = 0;
	for (int i = 0; i < N; i++) {
		string group[3];
		for (int j = 0; j < 3; j++) {
			fin >> group[j];
		}
		sort(group, group + 3);
		string sgroup = group[0] + ' ' + group[1] + ' ' + group[2];
		if (cowind.find(sgroup) == cowind.end()) {
			cowind[sgroup] = ind;
			occur[ind] = 1;
			ind++;
		}
		else {
			occur[cowind[sgroup]]++;
		}
	}
	int max = 0;
	for (auto i : occur) {
		if (i.second > max) {
			max = i.second;
		}
	}
	ofstream fout("records.out");
	fout << max << '\n';
}