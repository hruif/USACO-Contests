#include <iostream>
#include <fstream>
#include <unordered_set>
#include <algorithm>
#include <vector>

using namespace std;

struct pnt {
	int v;
	int ind;
	bool operator<(const pnt a) const {
		return v < a.v;
	}
};

int N;
pnt xs[1000];
pnt ys[1000];
int cows[1000][2];
unordered_set<int> t, b;

int main() {
	ifstream fin("balancing.in");
	ofstream fout("balancing.out");

	fin >> N;
	for (int i = 0; i < N; i++) {
		fin >> cows[i][0] >> cows[i][1];
		xs[i].ind = i;
		ys[i].ind = i;

		xs[i].v = cows[i][0];
		ys[i].v = cows[i][1];
	}
	sort(xs, xs + N);
	sort(ys, ys + N);

	int bestans = N;
	for (int i = 0; i < N - 1; i++) {
		t.clear();
		b.clear();
		for (int j = 0; j < N; j++) {
			if (xs[j].v <= xs[i].v) t.insert(xs[j].ind);
			else b.insert(xs[j].ind);
		}

		int tl = 0, tr = t.size();
		int bl = 0, br = b.size();
		for (int j = 0; j < N - 1; j++) {
			if (t.find(ys[j].ind) != t.end()) {
				tl++;
				tr--;
			}
			else {
				bl++;
				br--;
			}
			j++;
			while (j < N - 1 && ys[j].v == ys[j + 1].v) {
				if (t.find(ys[j].ind) != t.end()) {
					tl++;
					tr--;
				}
				else {
					bl++;
					br--;
				}
				j++;
			}
			j--;
			bestans = min(bestans, max(max(tl, tr), max(bl, br)));
		}
	}

	fout << bestans << '\n';
}