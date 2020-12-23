#include <iostream>
#include <fstream>

using namespace std;

int N;
int initialList[100];
int llist[101][2];


bool notSort() {
	for (int i = 0; i < N; i++) {
		if (initialList[i] != i + 1) {
			return true;
		}
	}
	return false;
}

int main() {
	ifstream fin("sleepy.in");
	ofstream fout("sleepy.out");

	fin >> N;
	for (int i = 0; i < N; i++) {
		fin >> initialList[i];
	}
	if (N == 1) {
		cout << "0\n";
	}
	else {
		int moves = 0;
		while (initialList[0] != 1 || notSort()) {
			int first = initialList[0];
			int place = N - 1;
			for (int i = N - 1; i >= 0; i--) {
				place = i;
				if (initialList[i] < first || (i < N - 1 && initialList[i] > initialList[i + 1])) {
					break;
				}
			}
			int ph = first;
			for (int i = place; i >= 0; i--) {
				int tmp = ph;
				ph = initialList[i];
				initialList[i] = tmp;
			}
			moves++;
		}
		fout << moves << '\n';
	}
}