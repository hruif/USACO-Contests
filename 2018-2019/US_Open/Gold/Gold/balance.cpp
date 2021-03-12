#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

#define ll long long

using namespace std;

int N;
int arr[200000];

ll last(vector<ll>& a) {
	return a[a.size() - 1];
}

int main() {
	ifstream fin("balance.in");
	ofstream fout("balance.out");

	fin >> N;
	for (int i = 0; i < 2 * N; i++) fin >> arr[i];

	ll linv = 0, rinv = 0;
	int os = 0;
	vector<ll> l0, l1, r0, r1;
	for (int i = 0; i < N; i++) {
		if (arr[i]) {	os++; l1.push_back(i);	}
		else {	linv += os; l0.push_back(i);	}
	}
	os = 0;
	for (int i = 2 * N - 1; i >= N; i--) {
		if (arr[i]) {	rinv += os; r1.push_back(i);	}
		else {	os++; r0.push_back(i);	}
	}
	vector<ll> tl0 = l0, tl1 = l1, tr0 = r0, tr1 = r1;

	ll swaps = abs(linv - rinv);
	ll nl = linv, nr = rinv;
	ll ts = 0;
	for (int i = 0; i < l1.size();) {
		if (r0.size() == 0) break;
		ts += last(r0) - last(l1);
		nl -= N - last(l1) - 1; nl += l1.size() - 1;
		nr -= last(r0) - N; nr += r0.size() - 1;
		ll dif = abs(nl - nr);
		l1.pop_back();
		r0.pop_back();

		ll ns = ts + dif;
		swaps = min(swaps, ns);
	}
	l1 = tl1, l0 = tl0, r0 = tr0, r1 = tr1;
	nl = linv, nr = rinv;
	ts = 0;
	for (int i = 0; i < r1.size();) {
		if (l0.size() == 0) break;
		ts += last(r1) - last(l0);
		nl += N - last(l0) - 1; nl -= l1.size();
		nr += last(r1) - N; nr -= r0.size();
		ll dif = abs(nl - nr);
		l0.pop_back();
		r1.pop_back();

		ll ns = ts + dif;
		swaps = min(swaps, ns);
	}

	fout << swaps << '\n';
}