#include <iostream>
#include <vector>
#include <utility>
#include <set>
#include <algorithm>

using namespace std;

const int inf = 1e8;
const int MAX_N = 200000;

int N;
int perm[MAX_N];
set<int> nums;
vector<pair<int, int>> segs;
vector<int> st;

void set_st(int n) {
	int sn = 1;
	while (sn < n) sn *= 2;
	st.resize(sn * 2, inf);
}

void change_val(int k, int x) {
	int sn = st.size() / 2;
	k += sn;
	st[k] = x;
	for (k /= 2; k >= 1; k /= 2) st[k] = min(st[k * 2], st[k * 2 + 1]);
}

int find_val(int a, int b) {
	int sn = st.size() / 2;
	a += sn; b += sn;
	int val = inf;
	while (a <= b) {
		if (a % 2 == 1) val = min(val, st[a++]);
		if (b % 2 == 0) val = min(val, st[b--]);
		a /= 2; b /= 2;
	}
	return val;
}

int main() {
	cin >> N;
	set_st(N + 2);
	for (int i = 0; i < N; i++) cin >> perm[i];
	for (int i = 0; i < N; i++) change_val(perm[i], i);
	//for (int i = 1; i <= N; i++) nums.insert(i);
	for (int i = 0; i < N; i++) {
		change_val(perm[i], inf);
		auto it = nums.lower_bound(perm[i]);
		int l = 0;
		if (it != nums.begin()) l = *(--it);
		int num = find_val(l, perm[i] - 1);
		if (num != inf) {
			l = perm[num];
			segs.push_back({ l, perm[i] - 1 });
		}
		nums.insert(perm[i]);
	}
	sort(segs.begin(), segs.end());
	int p = 0;
	set<int> rs;
	vector<int> ans;
	for (int i = 0; i <= N; i++) {
		int r = p;
		for (; r < segs.size() && segs[r].first <= i && segs[r].first == segs[p].first; r++) {
			rs.insert(segs[r].second);
		}
		while (!rs.empty() && *rs.begin() < i) rs.erase(rs.begin());
		ans.push_back(rs.size());
		p = r;
	}
	for (auto x : ans) cout << x << '\n';
}