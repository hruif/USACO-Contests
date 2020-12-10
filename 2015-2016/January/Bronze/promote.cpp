#include <iostream>
#include <fstream>

using namespace std;

int b1, b2;
int s1, s2;
int g1, g2;
int p1, p2;

int main() {
	ifstream fin("promote.in");
	ofstream fout("promote.out");

	fin >> b1 >> b2;
	fin >> s1 >> s2;
	fin >> g1 >> g2;
	fin >> p1 >> p2;

	int gtop = p2 - p1;
	g1 -= gtop;
	int stog = g2 - g1;
	s1 - stog;
	int btos = s2 - s1;
	fout << btos << '\n'
		<< stog << '\n'
		<< gtop << '\n';
}