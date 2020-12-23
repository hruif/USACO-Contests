#include <iostream>
#include <fstream>
#include <string>

using namespace std;

string s;
long long N;

int main() {
	ifstream fin("cowcode.in");
	ofstream fout("cowcode.out");

	fin >> s >> N;

	int rot = (N / s.size()) % s.size();

	fout << s[(rot + ((N - 1) % s.size())) % s.size()] << '\n';
}