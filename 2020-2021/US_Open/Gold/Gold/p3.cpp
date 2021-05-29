#include <iostream>
#include <fstream>

using namespace std;

int N;
int x[40], y[40];

int main() {
	cin >> N;

	for (int i = 0; i < N; i++) {
		cin >> x[i] >> y[i];
	}
	long long min3fac = 1;
	for (int i = 1; i <= N - 3; i++) {
		min3fac *= i;
		min3fac %= 1000000007;
	}

	long long cnt = 0;
	bool valid = false;
	for (int ii = 0; ii < N; ii++) {
		for (int ij = ii + 1; ij < N; ij++) {
			for (int ik = ij + 1; ik < N; ik++) {
				double s[3];
				double h[3];
				bool vert[] = { false, false, false };

				int i = ii, j = ij, k = ik;
				if (x)
				if (x[i] == x[j]) vert[0] = true;
				else {
					s[0] = (y[i] - y[j]) / (x[i] - x[j]);
					h[0] = y[i] - (s[0] * x[i]);
				}
				if (x[j] == x[k]) vert[1] = true;
				else {
					s[1] = (y[j] - y[k]) / (x[j] - x[k]);
					h[1] = y[j] - (s[1] * x[j]);
				}
				if (x[k] == x[i]) vert[2] = true;
				else {
					s[2] = (y[k] - y[i]) / (x[k] - x[i]);
					h[2] = y[k] - (s[2] * x[k]);
				}

				valid = true;
				int nofac = N - 3;
				for (int l = 0; l < N; l++) {
					if (l == i || l == j || l == k) continue;

					int ccc = 0;
					if ((vert[0] && x[k] < x[i] == x[l] < x[i]) ||
						(x[k] * s[0] + h[0] < y[k] == x[l] * s[0] + h[0] < y[l])) ccc++;
					if ((vert[1] && x[i] < x[j] == x[l] < x[j]) ||
						(x[i] * s[1] + h[1] < y[i] == x[l] * s[1] + h[1] < y[l])) ccc++;
					if ((vert[2] && x[j] < x[k] == x[l] < x[k]) ||
						(x[j] * s[2] + h[2] < y[j] == x[l] * s[2] + h[2] < y[l])) ccc++;
					if (ccc == 2) {
						nofac--;
					}
				}
				if (valid) {
					cnt += min3fac * nofac / (N - 3) * 6;
				}
			}
		}
	}
	cout << cnt << '\n';
}