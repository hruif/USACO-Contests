#include <iostream>
#include <fstream>

using namespace std;

int N;
bool cards[100005];

int main() {
	ifstream fin("highcard.in");
	ofstream fout("highcard.out");

	fin >> N;
	for (int i = 0; i < N; i++) {
		int card;
		fin >> card;
		cards[card] = true;
	}

	int fs = 0;
	int cnt = 0;
	for (int i = N * 2; i > 0; i--) {
		if (cards[i]) {
			if (fs > 0) {
				fs--;
				cnt++;
			}
		}
		else fs++;
	}

	fout << cnt << '\n';
}