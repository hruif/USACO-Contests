#include <iostream>
#include <algorithm>
using namespace std;

int N;
int p[100000], t[100000], a[100000];

int main() {
	cin >> N;
	for (int i = 0; i < N; i++) cin >> p[i];
	for (int i = 0; i < N; i++) cin >> t[i];
	for (int i = 0; i < N; i++) a[i] = p[i] - t[i];
	long long ans = 0;
	for (int i = 0; i < N;) {
		if (a[i] == 0) {
			continue;

		int p = i;
		int cur = a[i] / abs(a[i]);
		while (p < N && a[p] / abs(a[p]) == cur) p++;
		if (a[i] > 0) {
			ans += a[i];
			int last_v = a[i];
			for (int j = i + 1; j < p; j++) {
				if (a[j] > last_v) ans += a[j] - last_v;
				last_v = a[j];
			}
		}
		if (a[i] < 0) {
			ans += -a[i];
			int last_v = a[i];
			for (int j = i + 1; j < p; j++) {
				if (a[j] < last_v) ans += last_v - a[j];
				last_v = a[j];
			}
		}
		i = p;
	}
	cout << ans << '\n';
}
