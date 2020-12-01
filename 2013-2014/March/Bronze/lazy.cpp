#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

struct Point {
	int units;
	int location;
	Point() {}
	Point(int u, int l) {
		units = u;
		location = l;
	}
	bool operator<(const Point a) const {
		return location < a.location;
	}
};

int N, K;
Point patches[100000];

int main() {
	ifstream fin("lazy.in");
	ofstream fout("lazy.out");
	fin >> N >> K;
	for (int i = 0; i < N; i++) {
		int u, l;
		fin >> u >> l;
		patches[i] = Point(u, l);
	}
	sort(patches, patches + N);
	int ps = patches[0].units;
	int mps = ps;
	int l = 0;
	for (int i = 1; i < N; i++) {
		ps += patches[i].units;
		while (patches[i].location - patches[l].location > K * 2 + 1) {
			ps -= patches[l].units;
			l++;
		}
		if (ps > mps) {
			mps = ps;
		}
	}
	fout << mps << '\n';
}