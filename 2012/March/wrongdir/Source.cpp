#include <iostream>

using namespace std;

char intended[100000];
int revMove[100000][2];

int main() {
	cin >> intended;
	int end = 100000;
	for (int i = 99999; i >= 0; i--) {
		if (intended[i]) {
			break;
		}
		end = i;
	}
	int dir = 0;
	int forward = 0;
	int right = 0;
	for (int i = end - 1; i >= 0; i--) {
		if (intended[i] == 'F') {
			if (dir == 0) {
				forward++;
			}
			if (dir == 1) {
				right++;
			}
			if (dir == 2) {
				forward--;
			}
			if (dir == 3) {
				right--;
			}
		}
		if (intended[i] == 'L') {
			dir++;
			if (dir >= 4) {
				dir -= 4;
			}
		}
		if (intended[i] == 'R') {

		}
	}
}