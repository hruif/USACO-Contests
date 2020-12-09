#include <iostream>
#include <fstream>
#include <string>

#define ll long long

using namespace std;

int N;

int main() {
	ifstream fin("cow.in");
	ofstream fout("cow.out");

	ll c = 0, co = 0, total = 0;

	fin >> N;
	for (int i = 0; i < N; i++) {
		char l;
		fin >> l;
		if (l == 'C') c++;
		if (l == 'O') co += c;
		if (l == 'W') total += co;
	}

	fout << total << '\n';
}