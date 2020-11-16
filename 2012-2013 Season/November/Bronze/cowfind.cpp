#include <iostream>
#include <fstream>

using namespace std;

int N;
char grass[50000];
int legs[49999];

int main() {
	ifstream fin("input.in");
	fin >> grass;
	while (N < 50000 && grass[N]) {
		N++;
	}

	int ys = 0;
	for (int i = N - 2; i >= 0; i--) {
		if (grass[i] == ')' && grass[i + 1] == ')') {
			ys++;
		}
		legs[i] = ys;
	}
	int count = 0;
	for (int i = 0; i < N - 1; i++) {
		if (grass[i] == '(' && grass[i + 1] == '(') {
			count += legs[i];
		}
	}
	cout << count;
}