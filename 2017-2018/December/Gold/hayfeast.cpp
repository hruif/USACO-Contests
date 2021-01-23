#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

#define ll long long

using namespace std;

ll N, M;
int F[100000], S[100000];
vector<int> st;

int findm(int a, int b) {
	int sn = st.size() / 2;
	a += sn, b += sn;
	int s = 0;
	while (a <= b) {
		if (a % 2 == 1) s = max(s, st[a++]);
		if (b % 2 == 0) s = max(s, st[b--]);
		a /= 2, b /= 2;
	}
	return s;
}

void updst(int k, int x) {
	int sn = st.size() / 2;
	k += sn;
	st[k] = x;
	for (k /= 2; k >= 1; k /= 2) {
		st[k] = max(st[k * 2], st[k * 2 + 1]);
	}
}

void setst(int n, int* arr) {
	int sn = 1;
	while (sn < n) sn *= 2;
	sn *= 2;
	st.resize(sn, 0);
	for (int i = 0; i < n; i++) {
		updst(i, arr[i]);
	}
}

int main() {
	ifstream fin("hayfeast.in");
	ofstream fout("hayfeast.out");

	fin >> N >> M;
	for (int i = 0; i < N; i++) fin >> F[i] >> S[i];
	setst(N, S);

	ll f = 0;
	int p = 0;
	int ms = 1000000001;
	for (int i = 0; i < N; i++) {
		while (p < N && f < M) {
			f += F[p++];
		}
		if (p == N && f < M) break;
		ms = min(ms, findm(i, p - 1));
		f -= F[i];
	}

	fout << ms << '\n';
}