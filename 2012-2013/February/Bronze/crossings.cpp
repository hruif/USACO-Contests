#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_set>
#include <algorithm>

using namespace std;

struct Point {
	int x;
	int idx;
	bool operator<(Point a) {
		return x < a.x;
	}
	Point() {}
	Point(int x, int idx) {
		this->x = x;
		this->idx = idx;
	}
};

int N;
vector<Point> top;
vector<Point> bot;

int main() {
	ifstream fin("crossings.in");
	fin >> N;
	for (int i = 0; i < N; i++) {
		int b, t;
		fin >> b >> t;
		top.push_back(Point(t, i));
		bot.push_back(Point(b, i));
	}
	sort(top.begin(), top.end());
	sort(bot.begin(), bot.end());

	vector<bool> tCross(N, false);
	vector<bool> bCross(N, false);
	unordered_set<int> crossing;
	vector<bool> found(N, false);
	int tp = 0, bp = 0;
	while (tp < N || bp < N) {
		if (tp == N) {

		}
		else if (bp == N) {

		}
		else {
			if (top[tp].x < bot[bp].x) {
				if (!found[top[tp].idx]) {
					found[top[tp].idx] = true;
					crossing.insert(top[tp].idx);
				}
				tp++;
			}
			else {
				if (found[bot[bp].idx]) {
					crossing.erase(bot[bp].idx);
				}
				else {
					found[bot[bp].idx] = true;
					if (!crossing.empty()) {
						tCross[bot[bp].idx] = true;
					}
				}
			}
		}
	}
}