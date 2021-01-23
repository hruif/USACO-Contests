#include <iostream>
#include <fstream>
#include <algorithm>
#include <map>
#include <vector>

using namespace std;

int N;
int h[100000];
int sh[100000];
vector<int> st;
map<int, int> nums;

void setst(int n) {
	int sn = 1;
	while (sn < N) sn *= 2;
	st.resize(sn * 2, 0);
}

void add(int k, int x) {
	int sn = st.size() / 2;
	k += sn;
	st[k] = x;
	for (k /= 2; k >= 1; k /= 2) {
		st[k] = st[k * 2] + st[k * 2 + 1];
	}
}

int find(int a, int b) {
	int sn = st.size() / 2;
	a += sn, b += sn;
	int s = 0;
	while (a <= b) {
		if (a % 2 == 1) s += st[a++];
		if (b % 2 == 0) s += st[b--];
		a /= 2, b /= 2;
	}
	return s;
}

int main() {
	ifstream fin("bphoto.in");
	ofstream fout("bphoto.out");

	fin >> N;
	setst(N);
	for (int i = 0; i < N; i++) fin >> h[i];
	for (int i = 0; i < N; i++) sh[i] = h[i];
	sort(sh, sh + N);
	for (int i = 1; i <= N; i++) {
		nums[sh[i - 1]] = i;
	}

	int unbal = 0;
	for (int i = 0; i < N; i++) {
		int num = nums[h[i]];
		int L = find(num - 1, N - 1);
		int R = N - num - L;
		if (min(L, R) * 2 < max(L, R)) unbal++;
		add(num - 1, 1);
	}

	fout << unbal << '\n';
}