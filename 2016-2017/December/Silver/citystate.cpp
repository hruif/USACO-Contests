#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>

using namespace std;

int N;
unordered_map<string, long long> found;

int main() {
	ifstream fin("citystate.in");
	ofstream fout("citystate.out");

	long long total = 0;
	fin >> N;
	for (int i = 0; i < N; i++) {
		string city, state;
		fin >> city >> state;
		string cs = city.substr(0, 2);
		cs.push_back(state[0]);
		cs.push_back(state[1]);
		string sc = state.substr(0, 2);
		sc.push_back(city[0]);
		sc.push_back(city[1]);

		if (sc != cs) total += found[sc];
		found[cs]++;
	}
	fout << total << '\n';
}