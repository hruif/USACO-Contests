#include <iostream>
#include <fstream>

using namespace std;

int N;

char findChar(int n) {
	int len = 0, nLen = 3, layer = 0;
	while (nLen < n) {
		len = nLen;
		layer++;
		nLen *= 2;
		nLen += layer + 3;
	}
	if (nLen == n) {
		return ' ';
	}
	else if (len + layer + 3 >= n) {
		if (len + 1 == n) {
			return 'm';
		}
		else {
			return 'o';
		}
	}
	else {
		return findChar(n - (len + layer + 3));
	}
}

int main() {
	ifstream fin("moo.in");
	fin >> N;
	cout << findChar(N);
}