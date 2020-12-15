#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;

int N, K;
vector<int> bales;

bool canex(int r) {
	int k = 0;
	auto b = bales.begin();
	while (b != bales.end()) {
		if (k == K) return false;
		b = upper_bound(bales.begin(), bales.end(), *b + (r * 2));
		k++;
	}

	return true;
}

int main() {
	ifstream fin("angry.in");
	ofstream fout("angry.out");

	fin >> N >> K;
	bales.resize(N);
	for (int i = 0; i < N; i++) {
		fin >> bales[i];
	}
	sort(bales.begin(), bales.end());

	int l = 1;
	int r = 1000000000;
	while (l < r) {
 		int mid = (l + r) / 2;
		if (canex(mid)) r = mid;
		else l = mid + 1;
	}

	fout << l << '\n';
}