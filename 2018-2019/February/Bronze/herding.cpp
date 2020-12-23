#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

int cs[3];

int main() {
	ifstream fin("herding.in");
	ofstream fout("herding.out");

	fin >> cs[0] >> cs[1] >> cs[2];
	sort(cs, cs + 3);

	if (cs[2] - cs[1] == 1 && cs[1] - cs[0] == 1) fout << "0\n0\n";
	else {
		int minmoves = 1;
		if (cs[1] - cs[0] != 2 && cs[2] - cs[1] != 2) {
			minmoves = 2;
		}

		int maxmoves = max(cs[1] - cs[0], cs[2] - cs[1]) - 1;

		fout << minmoves << '\n' << maxmoves << '\n';
	}
}