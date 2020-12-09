#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

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
vector<Cow> points;

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
	int end = N - 1;
	while (start < N && cows[start].w < A) start++;
	while (end >= 0 && cows[end].w > B) end--;

	if (N == 1 || start == N || end < 0) {
		if (cows[0].s) {
			fout << B - A + 1 << '\n';
		}
		else {
			fout << 0 << '\n';
		}
	}
	else {
		if (start == 0) {
			points.push_back(Cow(cows[0].s, A));
			points.push_back(Cow(cows[0].s, (cows[0].w + cows[1].w) / 2));
		}
		else {
			points.push_back(Cow(cows[start - 1].s, A));
			points.push_back(Cow(cows[start - 1].s, (cows[start].w + cows[start - 1].w) / 2));
			points.push_back(Cow(cows[start].s, max(max((cows[start].w + cows[start - 1].w) / 2 + ((cows[start].w + cows[start - 1].w) % 2 == 1 ? 1 : 0), cows[start - 1].w + 1), A)));
			points.push_back(Cow(cows[start].s, (cows[start].w + cows[start + 1].w) / 2));
		}
		for (int i = start + 1; i < end; i++) {
			points.push_back(Cow(cows[i].s, max((cows[i].w + cows[i - 1].w) / 2 + ((cows[i].w + cows[i - 1].w) % 2 == 1 ? 1 : 0), cows[i - 1].w + 1)));
			points.push_back(Cow(cows[i].s, (cows[i].w + cows[i + 1].w) / 2));
		}
		if (end == N - 1) {
			points.push_back(Cow(cows[N - 1].s, (cows[N - 1].w + cows[N - 2].w) / 2));
			points.push_back(Cow(cows[N - 1].s, B));
		}
		else {
			points.push_back(Cow(cows[end].s, max((cows[end].w + cows[end - 1].w) / 2 + ((cows[end].w + cows[end - 1].w) % 2 == 1 ? 1 : 0), cows[end - 1].w + 1)));
			points.push_back(Cow(cows[end].s, min((cows[end].w + cows[end + 1].w) / 2, B)));
			points.push_back(Cow(cows[end + 1].s, max((cows[end].w + cows[end + 1].w) / 2 + ((cows[end].w + cows[end + 1].w) % 2 == 1 ? 1 : 0), cows[end].w + 1)));
			points.push_back(Cow(cows[end + 1].s, B));
		}
		int first = 0, last = points.size() - 1;
		if (points[0].w > points[1].w) {
			first += 2;
		}
		if (points[points.size() - 1] < points[points.size() - 2]) {
			last -= 2;
		}
		int cnt = 0;
		cows;
		for (int i = first; i < last; i += 2) {
			if (points[i].s) {
				if (i != first && points[i - 1].s) {
					cnt--;
				}
				cnt += points[i + 1].w - points[i].w + 1;
			}
		}
		fout << cnt << '\n';
	}
}