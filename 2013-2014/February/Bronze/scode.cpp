#include <iostream>
#include <fstream>
#include <string>

using namespace std;

string s;
bool lettin[26];

static int rback(string alt);
static int rfront(string alt);
static int afront(string original, string alt);

int aback(string original, string alt) {
	alt += original[original.size() - 1];
	if (alt == original) {
		return rback(alt) + rfront(alt) + 1;
	}
	return 0;
}

int afront(string original, string alt) {
	alt.insert(alt.begin(), original[0]);
	if (alt == original) {
		return rback(alt) + rfront(alt) + 1;
	}
	return 0;
}

int rback(string alt) {
	if (alt.size() % 2 == 0) {
		return 0;
	}
	string original = alt.substr(alt.size() / 2, alt.size() + 1);
	alt = alt.substr(0, alt.size() / 2);
	return afront(original, alt) + aback(original, alt);
}

int rfront(string alt) {
	if (alt.size() % 2 == 0) {
		return 0;
	}
	string original = alt.substr(0, alt.size() / 2 + 1);
	alt = alt.substr(alt.size() / 2 + 1, alt.size() / 2);
	return afront(original, alt) + aback(original, alt);
}

int main() {
	ifstream fin("scode.in");
	fin >> s;
	for (int i = 0; i < s.size(); i++) {
		lettin[s[i] - 'A'] = true;
	}
	int total = 0;
	int size = s.size();
	total += rfront(s);
	total += rback(s);

	ofstream fout("scode.out");
	fout << total << '\n';
}