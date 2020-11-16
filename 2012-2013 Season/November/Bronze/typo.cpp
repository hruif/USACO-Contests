#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

int N;
char s[100000];

int main() {
	ifstream fin("input.in");
	fin >> s;
	while (N < 100000 && s[N]) {
		N++;
	}
	
	int lc = 0, rc = 0;
	for (int i = 0; i < N; i++) {
		if (s[i] == '(') {
			lc++;
		}
		else {
			rc++;
		}
	}
	if (abs(lc - rc) != 2 || (s[0] == ')' && s[N - 1] == '(')) {
		cout << 0;
	}
	else {
		if (s[0] == ')' || s[N - 1] == '(') {
			cout << 1;
		}
		else {
			int count = 0;
			bool invalid = false;
			int rs = 0;
			for (int i = 0; i < N - 1; i++) {
				if (s[i] == ')') {
					if (rs <= 0) {
						if (rc > lc) {
							count++;
						}
					}
					if (rs >= 2) {
						invalid = true;
						break;
					}
					rs++;
				}
				if (s[i] == '(') {
					rs--;
				}
			}
			int ls = 0;
			for (int i = N - 1; i > 0; i--) {
				if (s[i] == '(') {
					if (ls <= 0) {
						if (lc > rc) {
							count++;
						}
					}
					if (ls >= 2) {
						invalid = true;
						break;
					}
					ls++;
				}
				if (s[i] == ')') {
					ls--;
				}
			}
			if (invalid) {
				cout << 0;
			}
			else {
				cout << count;
			}
		}
	}
}