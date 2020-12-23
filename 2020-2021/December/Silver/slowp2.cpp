#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_set>
#include <algorithm>

#define ll long long

using namespace std;

struct Point {
	int x;
	int y;
	Point() {}
	Point(int x, int y) {
		this->x = x;
		this->y = y;
	}
};

int N;
ll toignr[2500][2500];
ll abv[2500][2500];
ll bl[2500][2500];
Point cows[2500];

bool sortx(const Point a, const Point b) {
	return a.x < b.x;
}

bool sorty(const Point a, const Point b) {
	return a.y < b.y;
}

int main() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> cows[i].x >> cows[i].y;
	}
	sort(cows, cows + N, sortx);

	for (int i = 0; i < N; i++) {
		for (int j = i + 1; j < N; j++) {
			for (int k = i + 1; k < j; k++) {
				if ((cows[k].y < cows[i].y && cows[k].y > cows[j].y)
					|| (cows[k].y > cows[i].y && cows[k].y < cows[j].y)) {
					toignr[i][j]++;
				}
			}
		}
	}

	ll total = 0;
	for (int i = 0; i < N; i++) {
		ll above = 0;
		ll below = 0;
		for (int j = i + 1; j < N; j++) {
			if (cows[j].y < cows[i].y) {
				below++;
				total += (above + 1) * (below - toignr[i][j]);
			}
			else {
				above++;
				total += (below + 1) * (above - toignr[i][j]);
			}
		}
	}
	cout << total + N + 1 << '\n';
}