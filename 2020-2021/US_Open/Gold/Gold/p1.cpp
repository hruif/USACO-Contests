#include <iostream>
#include <fstream>
#include <queue>
#include <map>
#include <algorithm>
#include <vector>

using namespace std;

int N;
map<int, int> breeds;
vector<int> st;

void changeVal(int k, int x) {
	int sn = st.size() / 2;

	k += sn;
	st[k] = x;
	for (k /= 2; k >= 1; k /= 2) {
		st[k] = st[k * 2] + st[k * 2 + 1];
	}
}

int findSum(int a, int b) {
	int sn = st.size() / 2;

	a += sn; b += sn;
	int sum = 0;
	while (a <= b) {
		if (a % 2 == 1) sum += st[a++];
		if (b % 2 == 0) sum += st[b--];
		a /= 2;
		b /= 2;
	}
	return sum;
}

void setst(int n) {
	int sn = 1;
	while (sn < n) sn *= 2;
	st.resize(sn * 2, 0);
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);

	cin >> N;
	setst(N);
	long long cnt = 0;
	for (int i = 0; i < N; i++) {
		int b;
		cin >> b;
		b--;
		int prev = -1;
		if (breeds.find(b) != breeds.end()) {
			prev = breeds[b];
			changeVal(prev, 0);
		}
		breeds[b] = i;
		changeVal(i, 1);
		cnt += findSum(prev + 1, i - 1);
	}
	cout << cnt << '\n';
}