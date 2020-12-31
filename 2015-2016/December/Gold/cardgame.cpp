#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

int N;
int fh[25000];
int sh[25000];
bool ec[100001];

int main() {
	ifstream fin("cardgame.in");
	ofstream fout("cardgame.out");

	fin >> N;
	for (int i = 0; i < N / 2; i++) {
		fin >> fh[i];
		ec[fh[i]] = true;
	}
	for (int i = 0; i < N / 2; i++) {
		fin >> sh[i];
		ec[sh[i]] = true;
	}
	sort(fh, fh + (N / 2));
	sort(sh, sh + (N / 2));

	int ttl = 0;
	int p = N * 2;
	for (int i = (N / 2) - 1; i >= 0; i--) {
		for (; p > fh[i]; p--) {
			if (!ec[p]) {
				ec[p] = true;
				ttl++;
				break;
			}
		}
	}
	p = 1;
	for (int i = 0; i < N / 2; i++) {
		for (; p < sh[i]; p++) {
			if (!ec[p]) {
				ec[p] = true;
				ttl++;
				break;
			}
		}
	}
	
	fout << ttl << '\n';
}