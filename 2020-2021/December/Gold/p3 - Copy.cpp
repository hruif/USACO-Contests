#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <algorithm>
#include <cstdlib>

using namespace std;

int N;
vector<pair<int, int>> cows;

bool comps(pair<int, int>& a, pair<int, int>& b) {
	return a.second < b.second;
}

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
			vector<pair<int, int>> inr;
			inr.push_back(cows[i]);
			for (int j = i + 1; j < N; j++) {
				inr.push_back(cows[j]);
				sort(inr.begin(), inr.end(), comps);
				
				int curf = cows[j].first, curs = cows[j].second;
				int fd = abs(inif - curf); // first difference
				int sd = abs(inis - curs);
				if (fd >= sd) {
					int mis = max(inis, curs) - fd; // minimum second
					int mas = min(inis, curs);
					int ss = mis, bs = ss + fd; // small and big seconds
					int inri1 = -1, inri2;
					int maxi;
					for (int k = 0; k < inr.size(); k++) {
						int s = inr[k].second;
						if (s >= ss && inri1 == -1) inri1 = k;
						if (s <= bs) inri2 = k;
						if (s <= mas) maxi = k;
					}
					int p1 = inri1, p2 = inri2;
					if (maxi != inri2) {
						int a = 0;
					}
					while (ss <= mas && p1 <= maxi) {
						cnt++;
						if (inr[p1].second == ss && inr[p2].second == bs && ii == 0) {
							cnt--;
						}
						int d1 = inr[p1 + 1].second - ss, d2 = 1000000001;
						if (p2 < inr.size() - 1) d2 = inr[p2 + 1].second - bs;
						int dif = min(d2, d1);
						ss += dif; bs += dif;
						if (p2 < inr.size() - 1 && inr[p2 + 1].second <= bs) p2++;
						if (inr[p1].second < ss) p1++;
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