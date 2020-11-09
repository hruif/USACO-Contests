#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;

struct Rect {
	int x1;
	int y1;
	int x2;
	int y2;
	Rect() {};
	Rect(int x1, int y1, int x2, int y2) {
		this->x1 = x1;
		this->y1 = y1;
		this->x2 = x2;
		this->y2 = y2;
	}
};

int N;
vector<Rect> covered;

void alterRects(Rect rr) {
	int size = covered.size();
	for (int i = 0; i < size; i++) {
		Rect& r = covered[i];
		if (r.x1 >= rr.x2 || rr.x1 >= r.x2 || r.y2 >= rr.y1 || rr.y2 >= r.y1) {
			continue;
		}
		int rx1 = max(r.x1, rr.x1);
		int ry1 = min(r.y1, rr.y1);
		int rx2 = min(r.x2, rr.x2);
		int ry2 = max(r.y2, rr.y2);
		Rect r1(r.x1, r.y1, r.x2, ry1);
		Rect r2(r.x1, ry1, rx1, ry2);
		Rect r3(rx2, ry1, r.x2, ry2);
		Rect r4(r.x1, ry2, r.x2, r.y2);
		if (r1.x1 < r1.x2 && r1.y1 > r1.y2) {
			covered.push_back(r1);
		}
		if (r2.x1 < r2.x2 && r2.y1 > r2.y2) {
			covered.push_back(r2);
		}
		if (r3.x1 < r3.x2 && r3.y1 > r3.y2) {
			covered.push_back(r3);
		}
		if (r4.x1 < r4.x2 && r4.y1 > r4.y2) {
			covered.push_back(r4);
		}
		covered.erase(covered.begin() + i);
		i--;
		size--;
	}
	covered.push_back(rr);
}

int main() {
	ifstream fin("planting.in");
	fin >> N;
	for (int i = 0; i < N; i++) {
		Rect recreg;
		fin >> recreg.x1 >> recreg.y1 >> recreg.x2 >> recreg.y2;
		alterRects(recreg);
	}
	int totalCovered = 0;
	for (int i = 0; i < covered.size(); i++) {
		totalCovered += (covered[i].x2 - covered[i].x1) * (covered[i].y1 - covered[i].y2);
	}
	cout << totalCovered << '\n';
}