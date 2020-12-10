#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

int a, b, c, d;

int main() {
	ifstream fin("paint.in");
	ofstream fout("paint.out");

	fin >> a >> b >> c >> d;
	if (min(b, d) >= max(a, c)) {
		fout << max(d, b) - min(a, c) << '\n';
	}
	else {
		fout << (b - a) + (d - c) << '\n';
	}
}