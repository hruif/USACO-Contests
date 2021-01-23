#include <iostream>
#include <fstream>
#include <utility>
#include <queue>
#include <algorithm>

#define ll long long

using namespace std;

struct Point {
	ll dist;
	int x, y;
	Point() {}
	Point(int x, int y, ll dist) {
		this->x = x;
		this->y = y;
		this->dist = dist;
	}
	bool operator<(const Point a) const {
		return dist < a.dist;
	}
	bool operator>(const Point a) const {
		return dist > a.dist;
	}
};

ll A, B;
int n, m;
ll a[2002], b[2002];
bool visited[2002][2002];
priority_queue<Point, vector<Point>, greater<Point>> ps;

int main() {
	ifstream fin("fencedin.in");
	ofstream fout("fencedin.out");

	fin >> A >> B >> n >> m;
	a[0] = 0, b[0] = 0;
	for (int i = 1; i <= n; i++) fin >> a[i];
	for (int i = 1; i <= m; i++) fin >> b[i];
	sort(a + 1, a + n + 1);
	sort(b + 1, b + m + 1);
	a[n + 1] = A, b[m + 1] = B;

	int x = 0, y = 0;
	ps.push(Point(0, 0, 0));
	ll dist = 0;
	while (!ps.empty()) {
		Point p = ps.top();
		ps.pop();
		ll d = p.dist;
		int x = p.x, y = p.y;
		if (visited[x][y]) continue;
		visited[x][y] = true;
		dist += d;
		
		if (x < n && !visited[x + 1][y]) ps.push(Point(x + 1, y, b[y + 1] - b[y]));
		if (y < m && !visited[x][y + 1]) ps.push(Point(x, y + 1, a[x + 1] - a[x]));
		if (x > 0 && !visited[x - 1][y]) ps.push(Point(x - 1, y, b[y + 1] - b[y]));
		if (y > 0 && !visited[x][y - 1]) ps.push(Point(x, y - 1, a[x + 1] - a[x]));
	}
	fout << dist << '\n';
}