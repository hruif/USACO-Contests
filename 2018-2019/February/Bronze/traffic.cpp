#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

int N;
int dirs[100][3];

int main() {
	ifstream fin("traffic.in");
	ofstream fout("traffic.out");

	fin >> N;
	int l = 0, r = 1000;
	for (int i = 0; i < N; i++) {
		string s;
		int a, b;
		fin >> s >> a >> b;
		dirs[i][0] = a;
		dirs[i][1] = b;

		if (s == "on") {
			l += a;
			r += b;
			dirs[i][2] = 0;
		}
		if (s == "none") {
			l = max(l, a);
			r = min(r, b);
			dirs[i][2] = 1;
		}
		if (s == "off") {
			l -= b;
			r -= a;
			l = max(l, 0);
			dirs[i][2] = 2;
		}
	}
	int minl = l, minr = r;

	for (int i = N - 1; i >= 0; i--) {
		int a = dirs[i][0];
		int b = dirs[i][1];
		switch (dirs[i][2]) {
		case 0:
			l -= b;
			r -= a;
			l = max(l, 0);
			break;
		case 1:
			l = max(l, a);
			r = min(r, b);
			break;
		case 2:
			l += a;
			r += b;
			break;
		}
	}

	fout << l << ' ' << r << '\n'
		<< minl << ' ' << minr << '\n';
}