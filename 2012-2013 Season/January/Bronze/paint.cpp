#include <iostream>
#include <fstream>
#include <vector>
#include <utility>

using namespace std;

int N;
vector<pair<int, int>> segs;

int main() {
	ifstream fin("input.in");
	fin >> N;
	int x = 0;
	bool r = true;
	int total = 0;
	int covl = 1000000000, covr = -1000000000;
	for (int i = 0; i < N; i++) {
		int units;
		char dir;
		fin >> units >> dir;
		if (dir == 'R') {
			x += units;
		}
		else {
			x -= units;
		}
		for (int j = segs.size() - 1; j >= 0; j--) {
			if (r) {
				if (segs[j].second > x) {
					covr = max(covr, segs[j].second);
					if (segs[j].first >= x) {
						total += segs[j].second - segs[j].first;
						covl = min(covl, segs[j].first);
						segs.erase(segs.begin() + j);
					}
					else {
						total += segs[j].second - x;
						segs[j].second = x;
						covl = min(covl, segs[j].second);
					}
				}
			}
			else {
				if (segs[j].first < x) {
					covl = min(covl, segs[j].first);
					if (segs[j].second <= x) {
						total += segs[j].second - segs[j].first;
						covr = max(covr, segs[j].second);
						segs.erase(segs.begin() + j);
					}
					else {
						total += x - segs[j].first;
						segs[j].first = x;
						covr = max(covr, segs[j].first);
					}
				}
			}
		}
		if (x < 0) {
			r = false;
			if (x < covl) {
				segs.push_back({ x, covl });
			}
		}
		else {
			r = true;
			if (x > covr) {
				segs.push_back({ covr, x });
			}
		}
	}
	cout << total << '\n';
}