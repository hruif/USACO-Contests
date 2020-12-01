#include <iostream>
#include <fstream>

using namespace std;

int N;
int A[101];
int B[100];
int bInd[101];

int main() {
	ifstream fin("reorder.in");
	fin >> N;
	for (int i = 0; i < N; i++) {
		fin >> A[i];
	}
	A[N] = -1;
	for (int i = 0; i < N; i++) {
		fin >> B[i];
		bInd[B[i]] = i;
	}
	bool free = true;
	int maxlen = 0;
	int cnt = 0;
	while (free) {
		free = false;
		int p = N;
		for (int i = 0; i < N; i++) {
			if (A[i] != -1) {
				free = true;
				p = i;
				break;
			}
		}
		int len = 0;
		while (A[p] != -1) {
			int t = bInd[A[p]];
			A[p] = -1;
			p = t;
			len++;
		}
		if (len > maxlen) {
			maxlen = len;
		}
		if (len > 1) {
			cnt++;
		}
	}
	ofstream fout("reorder.out");
	fout << cnt << ' ' << maxlen << '\n';
}