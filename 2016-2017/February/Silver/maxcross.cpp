#include <iostream>
#include <fstream>

using namespace std;

int N, K, B;
int broken[100001];

int main() {
	ifstream fin("maxcross.in");
	ofstream fout("maxcross.out");

	fin >> N >> K >> B;
	for (int i = 0; i < B; i++) {
		int b;
		fin >> b;
		broken[b] = true;
	}
	int broke = 0;
	for (int i = 1; i <= K; i++) {
		if (broken[i]) {
			broke++;
		}
	}
	int minbreak = broke;
	for (int i = 1; i <= N - K; i++) {
		if (broken[i]) {
			broke--;
		}
		if (broken[i + K]) {
			broke++;
		}
		if (broke < minbreak) minbreak = broke;
	}
	fout << minbreak << '\n';
}