#include <iostream>
#include <fstream>
#include <algorithm>
#include <stack>
#include <unordered_map>
#include <vector>
#include <queue>

using namespace std;

int N, B;
int f[100000];
int sf[100000];
int sfgaps[100000];
unordered_map<int, int> sinds;

int main() {
	ifstream fin("snowboots.in");
	ofstream fout("snowboots.out");

	fin >> N >> B;
	for (int i = 0; i < N; i++) {
		fin >> f[i];
		sf[i] = f[i];
	}
	sort(sf, sf + N);
	//int n = 0;
	//for (int i = 0; i < N; i++) {
	//	int cur = sf[i];
	//	sinds[cur] = n++;
	//	while (i < N - 1 && sf[i + 1] == cur) i++;
	//}
	int j = 0;
	for (int i = 0; i < N; i++) {
		if (i == 0) {
			sinds[sf[i]] = j++;
		}
		else {
			if (sf[i] != sf[i - 1]) {
				sinds[sf[i]] = j++;
			}
		}
	}

	stack<pair<int, int>> heights;
	for (int i = 0; i < N; i++) {
		int back = i;
		int cur = f[i];
		while (!heights.empty() && heights.top().first >= cur) {
			back = heights.top().second;
			int dist = i - heights.top().second;
			int sfind = sinds[heights.top().first];
			sfgaps[sfind] = max(sfgaps[sfind], dist);
			heights.pop();
		}
		heights.push(make_pair(cur, back));
	}
	for (int i = j - 2; i >= 0; i--) {
		sfgaps[i] = max(sfgaps[i], sfgaps[i + 1]);
	}

	for (int i = 0; i < B; i++) {
		int s, d;
		fin >> s >> d;
		int p = upper_bound(sf, sf + N, s) - sf;
		if (p != N && sfgaps[sinds[sf[p]]] >= d) fout << "0\n";
		else fout << "1\n";
	}
}