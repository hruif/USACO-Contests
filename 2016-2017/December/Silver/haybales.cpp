#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

int N, Q;
int bales[100000];

int main() {
	ifstream fin("haybales.in");
	ofstream fout("haybales.out");

	fin >> N >> Q;
	for (int i = 0; i < N; i++) {
		fin >> bales[i];
	}
	sort(bales, bales + N);

	for (int i = 0; i < Q; i++) {
		int A, B;
		fin >> A >> B;
		int l = -1, r = N - 1;
		while (l < r - 1) {
			int mid = (l + r) / 2;
			if (bales[mid] < A) l = mid;
			else r = mid;
		}
		if (bales[r] < A) r++;
		int before = r;
		l = 0, r = N;
		while (l < r - 1) {
			int mid = (l + r) / 2;
			if (bales[mid] > B) r = mid;
			else l = mid;
		}
		fout << r - before << '\n';
	}
}