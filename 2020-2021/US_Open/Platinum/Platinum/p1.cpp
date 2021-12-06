#include <iostream>
#include <vector>

using namespace std;

int N;
int b[200000];
int nn[200000];
vector<int> st;

void set_st(int n) {
	int sn = 1;
	while (sn < n) sn *= 2;
	st.resize(sn * 2, 0);
}

void change_val(int k, int x) {
	int sn = st.size() / 2;
	k += 2;
	st[k] = x;
	for (k /= 2; k >= 1; k /= 2) {
		st[k] = st[k * 2] + st[k * 2 + 1];
	}
}

int find_val(int a, int b) {
	int sn = st.size() / 2;
	a += sn; b += sn;
	int v = 0;
	while (a <= b) {
		if (a % 2 == 1) v += st[a++];
		if (b % 2 == 0) v += st[b--];
		a /= 2; b /= 2;
	}
	return v;
}

int main() {
	cin >> N;
	for (int i = 0; i < N; i++) cin >> b[i];
	long long ans = 0;
	vector<int> ln(N + 1, N);
	for (int i = N - 1; i >= 0; i--) {
		nn[i] = ln[b[i]];
		ln[b[i]] = i;
	}
}