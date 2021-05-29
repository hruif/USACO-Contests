#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <utility>
#include <algorithm>

using namespace std;

int N, Q;
int fence[200000];
vector<pair<int, int>> pairs;
vector<pair<pair<int, int>, int>> queries;
int ses[200000][2]; // starts and ends
vector<int> st;

void setst(int n) {
	int sn = 1;
	while (sn < n) sn *= 2;
	st.resize(sn * 2, 0);
}

void changeVal(int k, int x) {
	int sn = st.size() / 2;

	k += sn;
	st[k] += x;
	for (k /= 2; k >= 1; k /= 2) {
		st[k] = st[k * 2] + st[k * 2 + 1];
	}
}

int findsum(int a, int b) {
	int sn = st.size() / 2;

	a += sn; b += sn;
	int sum = 0;
	while (a <= b) {
		if (a % 2 == 1) sum += st[a++];
		if (b % 2 == 0) sum += st[b--];
		a /= 2; b /= 2;
	}
	return sum;
}

int main() {
	cin >> N >> Q;
	setst(N);
	for (int i = 0; i < N; i++) {
		cin >> fence[i];
	}
	queries.resize(Q);
	for (int i = 0; i < Q; i++) {
		int a, b;
		cin >> a >> b;
		a--; b--;
		queries[i].first.first = b;
		queries[i].first.second = a;
		queries[i].second = i;
	}
	sort(queries.begin(), queries.end());

	stack<pair<int, int>> pairStarts;
	int s = 0, e = 0;
	int qp = 0;
	vector<int> qans(Q);
	for (int i = 0; i < N; i++) {
		int seg = fence[i];
		ses[i][0] = s;
		while (!pairStarts.empty() && pairStarts.top().first > seg) {
			pairStarts.pop();
		}
		if (!pairStarts.empty() && pairStarts.top().first == seg) {
			pairs.push_back({ pairStarts.top().second, i });
			changeVal(pairStarts.top().second, 1);
			pairStarts.top().second = i;
			e++;
		}
		else {
			pairStarts.push({ seg, i });
			s++;
		}
		ses[i][1] = e;
		while (qp < Q && queries[qp].first.first == i) {
			int i1 = queries[qp].first.second;
			qans[queries[qp].second] = i - i1 + 1 - findsum(i1, i);
			qp++;
		}
	}

	for (int i = 0; i < Q; i++) {
		cout << qans[i] << '\n';
	}
}