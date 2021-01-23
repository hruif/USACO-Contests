#include <iostream>
#include <fstream>
#include <vector>

#define ll long long

using namespace std;

int N, Q;
int A[5000];
int nums[2000001];
vector<ll> longs;
int ans[5000][5000];

ll addans(int i, int k) {
	int val = ans[i][k];
	if (val >= 0) return val;
	return longs[-val - 1];
}

int main() {
	ifstream fin("threesum.in");
	ofstream fout("threesum.out");

	fin >> N >> Q;
	for (int i = 0; i < N; i++) fin >> A[i];

	for (int i = 0; i < N; i++) {
		for (int k = i + 1; k < N; k++) {
			int jval = -(A[i] + A[k]);
			if (jval >= -1000000 && jval <= 1000000) ans[i][k] = nums[-(A[i] + A[k]) + 1000000];
			nums[A[k] + 1000000]++;
		}
		for (int k = i + 1; k < N; k++) nums[A[k] + 1000000]--;
	}
	int lcnt = 1;
	for (int i = N - 2; i >= 0; i--) {
		for (int k = i + 2; k < N; k++) {
			ll ltest = addans(i, k);
			ltest += addans(i + 1, k) + addans(i, k - 1) - addans(i + 1, k - 1);
			if (ltest <= 1000000000) ans[i][k] = ltest;
			else {
				ans[i][k] = -1 * lcnt++;
				longs.push_back(ltest);
			}
		}
	}
	for (int i = 0; i < Q; i++) {
		ll a, b;
		fin >> a >> b;
		if (b < a) swap(a, b);
		ll val = ans[a - 1][b - 1];
		if (val < 0) val = longs[-val - 1];
		fout << val << '\n';
	}
}