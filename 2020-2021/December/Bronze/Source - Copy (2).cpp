#include <iostream>
#include <algorithm>
using namespace std;

int N;
int flows[100];

int main() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> flows[i];
	}
	int avgflps = 0;
	for (int i = 0; i < N; i++) {
		int tpets = 0;
		for (int j = i; j < N; j++) {
			tpets += flows[j];
			int nflows = j - i + 1;
			if (tpets % nflows != 0) continue;
			int avg = tpets / nflows;
			for (int p = i; p <= j; p++) {
				if (flows[p] == avg) {
					avgflps++;
					break;
				}
			}
		}
	}
	cout << avgflps << '\n';
}