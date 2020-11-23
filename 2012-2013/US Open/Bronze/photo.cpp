#include <iostream>
#include <fstream>
#include <algorithm>
#include <unordered_set>

using namespace std;

struct Cow {
	int id;
	int ind;
	bool operator<(const Cow a) const{
		return id < a.id;
	}
	Cow() {
		id = -1;
		ind = -1;
	}
	Cow(int id, int ind) {
		this->id = id;
		this->ind = ind;
	}
};

Cow cows[2000];
unordered_set<int> inds;

int main() {
	ifstream fin("photo.in");
	int N, K;
	fin >> N >> K;
	for (int i = 0; i < K; i++) {
		int A, B;
		fin >> A >> B;
		cows[i * 2] = Cow(A, i);
		cows[i * 2 + 1] = Cow(B, i);
	}
	sort(cows, cows + (K * 2));
	int count = 0;
	for (int i = 0; i < K * 2; i++) {
		if (inds.find(cows[i].ind) == inds.end()) {
			inds.insert(cows[i].ind);
		}
		else {
			count++;
			inds.clear();
			int curid = cows[i].id;
			while (i < K * 2 && cows[i].id == curid) {
				i++;
			}
			i--;
		}
	}
	ofstream fout("photo.out");
	fout << count + 1 << '\n';
}