#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_set>
#include <algorithm>

#define ll long long
#define INF 10e16

using namespace std;

int N;
vector<int> blocks[1000];
vector<int> interact[1000];
int blame[1000];
ll dists[1000];
ll cows[1000][3];

ll findcoltime(int c1, int c2) {
	ll x1 = cows[c1][0], y1 = cows[c1][1], d1 = cows[c1][2];
	ll x2 = cows[c2][0], y2 = cows[c2][1], d2 = cows[c2][2];

	ll dst1 = y2 - y1;
	ll dst2 = x1 - x2;
	if (dst1 > dists[c1] || dst2 > dists[c2] || dst1 == dst2) return INF;
	return max(dst1, dst2);
}

ll firstStopTime(int& a, int& b) {
	ll mincoltime = INF;
	for (int i = 0; i < N - 1; i++) {
		ll x1 = cows[i][0], y1 = cows[i][1], d1 = cows[i][2];
		for (int p = 0; p < interact[i].size(); p++) {
			int j = interact[i][p];
			ll x2 = cows[j][0], y2 = cows[j][1], d2 = cows[j][2];
			
			if (d1 == d2) continue;

			int c1, c2;
			if (d1 == 0) {
				if (y1 > y2 || x2 > x1) continue;
				c1 = i, c2 = j;
			}
			else {
				if (x1 > x2 || y2 > y1) continue;
				c1 = j, c2 = i;
			}
			ll coltime = findcoltime(c1, c2);
			if (coltime < mincoltime) {
				mincoltime = coltime;
				a = i;
				b = j;
			}
		}
	}
	return mincoltime;
}

void updBlame(ll firstcoltime, int i, int j) {
	ll x1 = cows[i][0], y1 = cows[i][1], d1 = cows[i][2];
	ll x2 = cows[j][0], y2 = cows[j][1], d2 = cows[j][2];

	int c1, c2;
	if (d1 == 0) {

		ll dst1 = y2 - y1;
		ll dst2 = x1 - x2;
		if (dst1 > dst2) {
			if (dst1 == firstcoltime) {
				dists[i] = dst1 - 1;
				blocks[j].push_back(i);
				return;
			}
		}
		else {
			if (dst2 == firstcoltime) {
				dists[j] = dst2 - 1;
				blocks[i].push_back(j);
				return;
			}
		}
	}
	else {
		ll dst1 = x2 - x1;
		ll dst2 = y1 - y2;
		if (dst1 > dst2) {
			if (dst1 == firstcoltime) {
				dists[i] = dst1 - 1;
				blocks[j].push_back(i);
				return;
			}
		}
		else {
			if (dst2 == firstcoltime) {
				dists[j] = dst2 - 1;
				blocks[i].push_back(j);
				return;
			}
		}
	}
}

bool taken[1000];
void takeblame(int c) {
	if (taken[c]) return;
	taken[c] = true;
	for (int i = 0; i < blocks[c].size(); i++) {
		takeblame(blocks[c][i]);
		blame[c] += blame[blocks[c][i]] + 1;
	}
}

int main() {
	for (int i = 0; i < 1000; i++) dists[i] = INF;

	cin >> N;
	for (int i = 0; i < N; i++) {
		char dir;
		cin >> dir >> cows[i][0] >> cows[i][1];
		if (dir == 'N') cows[i][2] = 0;
		else cows[i][2] = 1;
	}

	for (int i = 0; i < N - 1; i++) {
		ll x1 = cows[i][0], y1 = cows[i][1], d1 = cows[i][2];
		for (int j = i + 1; j < N; j++) {
			ll x2 = cows[j][0], y2 = cows[j][1], d2 = cows[j][2];
			if (cows[i][2] == cows[j][2]) continue;

			if (d1 == 0) {
				ll dst1 = y2 - y1;
				ll dst2 = x1 - x2;
				if (dst1 == dst2 || dst1 < 0 || dst2 < 0) continue;
				interact[i].push_back(j);
				interact[j].push_back(i);
			}
			else {
				ll dst1 = x2 - x1;
				ll dst2 = y1 - y2;
				if (dst1 == dst2 || dst1 < 0 || dst2 < 0) continue;
				interact[i].push_back(j);
				interact[j].push_back(i);
			}
		}
	}

	int a, b;
	ll firstcol = firstStopTime(a, b);
	while (firstcol != INF) {
		updBlame(firstcol, a, b);
		firstcol = firstStopTime(a, b);
	}
	for (int i = 0; i < N; i++) {
		takeblame(i);
	}
	for (int i = 0; i < N; i++) {
		cout << blame[i] << '\n';
	}
}