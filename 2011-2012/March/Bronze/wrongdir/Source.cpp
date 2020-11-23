#include <iostream>
#include <unordered_set>

using namespace std;

char intended[100000];
int originalPath[100000][3];
int relatives[100000][2];
unordered_set<long long> foundPoints;

long long pToLL(int x, int y) {
	long long ll = x;
	for (int i = 0; i < 32; i++) {
		ll <<= 1;
	}
	ll += y;
	return ll;
}

void addPoint(int i, int x, int y, int dir) {
	switch (dir) {
	case 0:
		y += relatives[i][0];
		x += relatives[i][1];
	case 1:
		x += relatives[i][0];
		y -= relatives[i][1];
	case 2:
		y -= relatives[i][0];
		x -= relatives[i][1];
	case 3:
		x -= relatives[i][0];
		y += relatives[i][1];
	}
	foundPoints.insert(pToLL(x, y));
}

int main() {
	cin >> intended;
	int end = 100000;
	for (int i = 99999; i >= 0; i--) {
		if (intended[i]) {
			break;
		}
		end = i;
	}

	int x = 0, y = 0;
	int dir = 0;
	for (int i = 0; i < end; i++) {
		if (intended[i] == 'R') {
			dir++;
			if (dir == 4) {
				dir = 0;
			}
		}
		else if (intended[i] == 'L') {
			dir--;
			if (dir < 0) {
				dir = 3;
			}
		}
		else {
			switch (dir) {
			case 0:
				y++;
			case 1:
				x++;
			case 2:
				y--;
			case 3:
				x--;
			}
		}
		originalPath[i][0] = x;
		originalPath[i][1] = y;
		originalPath[i][2] = dir;
	}

	int endx = x, endy = y;
	x = y = 0;
	for (int i = 0; i < end; i++) {
		x = originalPath[i][0];
		y = originalPath[i][1];
		dir = originalPath[i][2];
		switch (dir) {
		case 0:
			relatives[i][0] = endy - y;
			relatives[i][1] = endx - x;
		case 1:
			relatives[i][0] = endx - x;
			relatives[i][1] = y - endy;
		case 2:
			relatives[i][0] = y - endy;
			relatives[i][1] = x - endx;
		case 3:
			relatives[i][0] = x - endx;
			relatives[i][1] = endy - y;
		}
	}


	x = y = 0;
	if (intended[0] != 'F') {
		addPoint(0, 0, 1, 0);
	}
	if (intended[0] != 'R') {
		addPoint(0, 0, 0, 1);
	}
	if (intended[0] != 'L') {
		addPoint(0, 0, 0, 3);
	}
	for (int i = 1; i < end; i++) {
		x = originalPath[i][0];
		y = originalPath[i][1];
		if (intended[i] != 'R') {
			addPoint(i, x, y, originalPath[i - 1][2] + 1);
		}
		if (intended[i] != 'L') {
			addPoint(i, x, y, originalPath[i - 1][2] - 1);
		}
		if (intended[i] != 'F') {
			switch (dir) {
			case 0:
				y++;
			case 1:
				x++;
			case 2:
				y--;
			case 3:
				x--;
			}
			addPoint(i, x, y, originalPath[i - 1][2]);
		}
	}
	int count = 0;
	for (auto i : foundPoints) {
		count++;
	}
	cout << count;
}