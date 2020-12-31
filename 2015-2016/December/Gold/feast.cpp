#include <iostream>
#include <fstream>

using namespace std;

int T, A, B;
bool canget[5000010];

int main() {
	ifstream fin("feast.in");
	ofstream fout("feast.out");

	fin >> T >> A >> B;
	canget[0] = true;
	for (int i = 0; i <= T; i++) {
		if (canget[i]) {
			if (i + A <= T) canget[i + A] = true;
			if (i + B <= T) canget[i + B] = true;
		}
	}
	for (int i = 1; i <= T; i++) {
		if (i * 2 > T) break;
		if (canget[i * 2] || canget[i * 2 + 1]) canget[i] = true;
	}
	for (int i = 0; i <= T; i++) {
		if (canget[i]) {
			if (i + A <= T) canget[i + A] = true;
			if (i + B <= T) canget[i + B] = true;
		}
	}

	int ans = 0;
	for (int i = T; i >= 0; i--) {
		if (canget[i]) {
			ans = i;
			break;
		}
	}

	fout << ans << '\n';
}