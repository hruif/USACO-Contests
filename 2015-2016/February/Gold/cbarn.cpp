#include <iostream>
#include <fstream>

#define ll long long

using namespace std;

int n;
int c[100000];
int moved[100000];

int main() {
	ifstream fin("cbarn.in");
	ofstream fout("cbarn.out");

	fin >> n;
	for (int i = 0; i < n; i++) fin >> c[i];

	ll dist = 0;
	for (int i = n - 1; i >= 0; i--) {
		if (c[i] == 0) {
			for (ll j = 1; j < n; j++) {
				int p = (i - j + n) % n;
				if (c[p] > 0) {
					c[p]--;
					c[i]++;

					ll m = moved[p];
					dist -= m * m;
					dist += (j + m) * (j + m);
					moved[p] = 0;
					moved[i] = j + m;
					break;
				}
			}
		}
	}
	for (int i = n - 1; i >= 0; i--) {
		if (c[i] == 0) {
			for (ll j = 1; j < n; j++) {
				int p = (i - j + n) % n;
				if (c[p] > 0) {
					c[p]--;
					c[i]++;

					ll m = moved[p];
					dist -= m * m;
					dist += (j + m) * (j + m);
					moved[p] = 0;
					moved[i] = j + m;
					break;
				}
			}
		}
	}
	fout << dist << '\n';
}