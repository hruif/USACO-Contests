#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

int N;
int bales[100];

int main() {
	ifstream fin("angry.in");
	ofstream fout("angry.out");

	fin >> N;
	for (int i = 0; i < N; i++) {
		fin >> bales[i];
	}
	sort(bales, bales + N);

	int maxe = 0;
	for (int i = 0; i < N; i++) {
		int es = 1;

		int r = i;
		int pr = i;
		int re = 1;
		while (true) {
			while (r < N && bales[r] - bales[pr] <= re) {
				r++;
			}
			r--;
			if (r > pr) {
				pr = r;
				re++;
			}
			else break;
		}

		int l = i;
		int pl = i;
		int le = 1;
		while (true) {
			while (l >= 0 && bales[pl] - bales[l] <= le) {
				l--;
			}
			l++;
			if (l < pl) {
				pl = l;
				le++;
			}
			else break;
		}

		int total = r - l + 1;
		if (total > maxe) maxe = total;
	}

	fout << maxe << '\n';
}