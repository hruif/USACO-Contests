#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>

using namespace std;

int N;
int points[50000][2];
unordered_map<int, int> xs, ys;

int main() {
	ifstream fin("input.in");
	fin >> N;
	for (int i = 0; i < N; i++) {
		fin >> points[i][0] >> points[i][1];
		if (xs.find(points[i][0]) != xs.end()) {
			xs[points[i][0]]++;
		}
		else {
			xs[points[i][0]] = 1;
		}
		if (ys.find(points[i][1]) != ys.end()) {
			ys[points[i][1]]++;
		}
		else {
			ys[points[i][1]] = 1;
		}
	}

	if (xs.size() <= 3 || ys.size() <= 3) {
		cout << 1;
	}
	else {
		bool working = false;
		for (auto i : xs) {
			for (auto j : xs) {
				if (i.first >= j.first) {
					continue;
				}
				for (int k = 0; k < N; k++) {
					if (points[k][0] == i.first || points[k][0] == j.first) {
						ys[points[k][1]]--;
					}
				}
				int count = 0;
				for (auto k : ys) {
					if (k.second > 0) {
						count++;
					}
					if (count > 1) {
						break;
					}
				}
				for (int k = 0; k < N; k++) {
					if (points[k][0] == i.first || points[k][0] == j.first) {
						ys[points[k][1]]++;
					}
				}
				if (count <= 1) {
					working = true;
					break;
				}
			}
			if (working) {
				break;
			}
		}

		for (auto i : ys) {
			for (auto j : ys) {
				if (i.first > j.first) {
					continue;
				}
				for (int k = 0; k < N; k++) {
					if (points[k][1] == i.first || points[k][1] == j.first) {
						xs[points[k][0]]--;
					}
				}
				int count = 0;
				for (auto k : xs) {
					if (k.second > 0) {
						count++;
					}
					if (count > 1) {
						break;
					}
				}
				for (int k = 0; k < N; k++) {
					if (points[k][1] == i.first || points[k][1] == j.first) {
						xs[points[k][0]]++;
					}
				}
				if (count <= 1) {
					working = true;
					break;
				}
			}
			if (working) {
				break;
			}
		}
		if (working) {
			cout << 1;
		}
		else {
			cout << 0;
		}
	}
}