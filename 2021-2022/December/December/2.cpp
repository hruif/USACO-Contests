#include <iostream>
#include <vector>
#include <utility>

using namespace std;

const int MAX_N = 200000;

int N;
int perm[MAX_N];
vector<pair<int, int>> segs;
vector<int> st;

void set_st(int n) {
	int sn = 1;
	while (sn < n) sn *= 2;
	st.resize(sn * 2, 0);
}

void change_val(int k) {
	int sn = st.size() / 2;
	k += sn;
	st[k]++;
	for (k /= 2; k >= 1; k /= 2) st[k] = st[k * 2] + st[k * 2 + 1];
}

int find_val(int a, int b) {
	int sn = st.size() / 2;
	a += sn; b += sn;
	int val = 0;
	while (a <= b) {
		if (a % 2 == 1) val += st[a++];
		if (b % 2 == 0) val += st[b--];
		a /= 2; b /= 2;
	}
	return val;
}

int main() {
	cin >> N;
	for (int i = 0; i < N; i++) cin >> perm[i];
	for (int i = 0; i < N; i++) {

	}
}