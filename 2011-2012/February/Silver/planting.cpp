#include <iostream>
#include <fstream>
#include <vector>

#define ll long long

using namespace std;

struct Rect {
	ll x1;
	ll y1;
	ll x2;
	ll y2;
	Rect() {}
	Rect(ll x1, ll y1, ll x2, ll y2) {
		this->x1 = x1;
		this->y1 = y1;
		this->x2 = x2;
		this->y2 = y2;
	}
};

int N;
vector<Rect> rects;

void placeRect(Rect rect) {
	int size = rects.size();
	for (int i = 0; i < size; i++) {
		Rect& r = rects[i];
		if (r.x1 > rect.x2 || rect.x1 > r.x2 || r.y1 < rect.y2 || rect.y1 < r.y2) {
			continue;
		}
		Rect r1(r.x1, r.y1, rect.x1, r.y2);
		Rect r2(max(r.x1, rect.x1), r.y1, min(r.x2, rect.x2), rect.y1);
		Rect r3(rect.x2, r.y1, r.x2, r.y2);
		Rect r4(max(r.x1, rect.x1), rect.y2, min(r.x2, rect.x2), r.y2);
		if (r1.x1 < r1.x2 && r1.y1 > r1.y2) {
			rects.push_back(r1);
		}
		if (r2.x1 < r2.x2 && r2.y1 > r2.y2) {
			rects.push_back(r2);
		}
		if (r3.x1 < r3.x2 && r3.y1 > r3.y2) {
			rects.push_back(r3);
		}
		if (r4.x1 < r4.x2 && r4.y1 > r4.y2) {
			rects.push_back(r4);
		}
		rects.erase(rects.begin() + i);
		i--;
		size--;
	}
	rects.push_back(rect);
}

int main() {
	ifstream fin("planting.in");
	fin >> N;
	for (int i = 0; i < N; i++) {
		int x1, y1, x2, y2;
		fin >> x1 >> y1 >> x2 >> y2;
		placeRect(Rect(x1, y1, x2, y2));
	}
	ofstream fout("planting.out");
	ll total = 0;
	for (auto i : rects) {
		total += (i.x2 - i.x1) * (i.y1 - i.y2);
	}
	fout << total << '\n';
}