#include <iostream>
#include <fstream>
#include <algorithm>
#include <unordered_set>

using namespace std;

struct Point {
	int temp;
	int ind;
	Point() {}
	Point(int temp, int ind) {
		this->temp = temp;
		this->ind = ind;
	}
	bool operator<(const Point a) const {
		return temp < a.temp;
	}
};

int N, X, Y, Z;
Point points[40000];

unordered_set<int> setps;
int main() {
	ifstream fin("milktemp.in");
	fin >> N >> X >> Y >> Z;
	for (int i = 0; i < N; i++) {
		int t1, t2;
		fin >> t1 >> t2;
		points[i * 2] = Point(t1, i);
		points[i * 2 + 1] = Point(t2, i);
	}
	sort(points, points + N * 2);
	int pos = 0;
	int max = 0;
	int curMilk = N * X;
	int nextMilk = N * X;
	while (pos < N * 2) {
		int temp = points[pos].temp;
		curMilk = nextMilk;
		while (points[pos].temp == temp && pos < N * 2) {
			if (setps.find(points[pos].ind) == setps.end()) {
				setps.insert(points[pos].ind);
				curMilk += Y - X;
				nextMilk += Y - X;
			}
			else {
				setps.erase(setps.find(points[pos].ind));
				nextMilk -= Y - Z;
			}
			pos++;
		}
		if (curMilk > max) {
			max = curMilk;
		}
	}
	ofstream fout("milktemp.out");
	fout << max << '\n';
}