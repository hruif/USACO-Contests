#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

struct Cow {
	bool s;
	int w;
	Cow() {}
	Cow(bool s, int w) {
		this->s = s;
		this->w = w;
	}
	bool operator<(const Cow a) const {
		return w < a.w;
	}
};

int N, A, B;
Cow cows[50000];

int main() {
	ifstream fin("learning.in");
	ofstream fout("learning.out");

	fin >> N >> A >> B;
	for (int i = 0; i < N; i++) {
		char cs;
		fin >> cs;
		bool s = false;
		if (cs == 'S') s = true;
		else fin >> cs;
		int w;
		fin >> w;
		cows[i] = Cow(s, w);
	}
	sort(cows, cows + N);

	int start = 0;
	int cnt = 0;
	for (int i = 0; i < N; i++) {
		if (cows[i].w > A) {
			break;
		}
		start = i;
	}
	if (start == N - 1) {
		if (cows[start].s) {
			fout << B - A + 1 << '\n';
		}
		else {
			fout << 0 << '\n';
		}
	}
	else if (N == 1) {
		if (cows[0].s) {
			fout << B - A + 1 << '\n';
		}
		else {
			fout << 0 << '\n';
		}
	}
	else {
		while (start < N && cows[start].w < B) {
			while (start < N && !cows[start].s) start++;
			if (start == N) {
				break;
			}
			if (cows[start].w >= B) {
				break;
			}
			if (start == 0) {
				int mid = (cows[1].w + cows[0].w) / 2; // mid of cow 0 and cow 1
				if (cows[1].s && (cows[1].w + cows[0].w) % 2 == 0) {
					cnt += cows[0].w - A // from A to cows[0].w
						+ min(mid - 1, B) - cows[0].w // from cows[0].w to mid - 1
						+ 1; // including point itself
				}
				else {
					cnt += cows[0].w - A
						+ min(mid, B) - cows[0].w + 1;
				}
			}
			else if (start == N - 1) {
				int mid = max((cows[N - 2].w + cows[N - 1].w) / 2, A);
				cnt += cows[N - 1].w - mid + (B - cows[N - 1].w) + 1;
				if (cows[start].w - 1 == cows[start - 1].w) {
					cnt--;
				}
			}
			else {
				int lmid = max((cows[start].w + cows[start - 1].w) / 2, A);
				int rmid = min((cows[start].w + cows[start + 1].w) / 2, B);
				cnt += cows[start].w - lmid; // from lmid to start
				cnt += rmid - cows[start].w; // from rmid to start
				cnt++; // count start
				if (rmid == (cows[start].w + cows[start + 1].w) / 2 && (cows[start].w + cows[start + 1].w) % 2 == 0) {
					cnt--; // subtract if will count rmid twice
				}
				if (cows[start].w - 1 == cows[start - 1].w) {
					cnt--;
				}
			}
			start++;
		}

		if (start < N) {
			if (cows[start - 1].w < B && cows[start].s) {
				int lmid = min((cows[start].w + cows[start - 1].w) / 2, B);
				if ((cows[start].w + cows[start - 1].w) / 2 <= B) {
					if ((cows[start].w + cows[start - 1].w) / 2 == B && ((cows[start].w + cows[start - 1].w) % 2 == 0)) {
						cnt++;
					}
					cnt += B - lmid;
				}
			}
		}

		fout << cnt << '\n';
	}
}