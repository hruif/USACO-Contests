#include <iostream>
#include <fstream>

using namespace std;

int N, K;
int bits[];

int combos(int nb, int k) {
	long long total = 1;
	for (long long i = nb; i > nb - k; i--) {
		total *= i;
	}
	for (long long i = 1; i <= k; i++) {
		total /= i;
	}
	return total;
}

int main() {
	ifstream fin("cowids.in");
	ofstream fout("cowids.out");
	fin >> N >> K;
	int nb = 0; // number of bits
	int total = 0;
	if (K == 1) {
		fout << 1;
		for (int i = 1; i < N; i++) {
			fout << 0;
		}
	}
	else {
		while (total < N) {
			nb++;
			total += combos(nb, K - 1);
		}
		total -= combos(nb, K - 1);
		nb++;
		N -= total;
		K--;
		fout << 1;
		int ob = 1; // on bit
		for (int i = nb - 1; i >= 1; i--) {
			int t = combos(i - 1, K);
			if (N > t && N != 0) {
				N -= t;
				K--;
				fout << 1;
			}
			else {
				fout << 0;
			}
		}
	}
	fout << '\n';
}