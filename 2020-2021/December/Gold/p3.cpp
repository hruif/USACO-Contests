#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <algorithm>
#include <cstdlib>
#include <set>

using namespace std;

int N;
vector<pair<int, int>> cows;

struct SortByY {
	bool operator()(const pair<int, int>& a, const pair<int, int>& b) const {
		return a.second < b.second;
	}
};

int main() {
	cin >> N;
	cows.resize(N);
	for (int i = 0; i < N; i++) cin >> cows[i].first >> cows[i].second;
	int cnt = 0;
	for (int ii = 0; ii < 2; ii++) {
		sort(cows.begin(), cows.end());
		for (int i = 0; i < N; i++) {
			int inif = cows[i].first; // initial first
			int inis = cows[i].second;
			set<pair<int, int>, SortByY> inr;
			inr.insert(cows[i]);
			for (int j = i + 1; j < N; j++) {
				inr.insert(cows[j]);
				
				int curf = cows[j].first, curs = cows[j].second;
				int fd = abs(inif - curf); // first difference
				int sd = abs(inis - curs);
				int mis = min(inis, curs), mas = max(inis, curs);
				if (fd >= sd) {
					vector<pair<int, int>> a, b;
					for (auto i : inr) {
						if (i.second >= mas - fd && i.second <= mis) a.push_back(i);
						if (i.second <= mis + fd && i.second >= mas) b.push_back(i);
					}
					int bp = 0;
					int ps = -1000000000;
					for (int ap = 0; ap < a.size(); ap++) {
						while (bp < b.size() && a[ap].second + fd >= b[bp].second) {
							if (a[ap].second + fd != b[bp].second || ii) {
								if (bp == b.size() - 1 || b[bp + 1].second - 1 >= ps + fd + 1) {
									cnt++;
								}
							}
							bp++;
						}
						if (bp > 0) bp--;
						ps = a[ap].second;
					}
				}
			}
		}
		for (int i = 0; i < N; i++) {
			swap(cows[i].first, cows[i].second);
		}
	}
	cout << cnt + N + 1 << '\n';
}