#include <iostream>
#include <fstream>
#include <string>

#define ll long long

using namespace std;

string X, Y;

int findmoos(string a, string b) {
	ll al = stoll(a);
	ll bl = stoll(b);
	int moos = 0;
	for (int i = a.size(); i <= b.size(); i++) {
		for (int j = 1; j <= 9; j++) {
			for (int k = i - 1; k >= 0; k--) { // excluding
				for (int l = 0; l <= 9; l++) {
					if (l == j) continue;
					string s = "";
					for (int p = 0; p < i; p++) {
						if (k == 0) {
							if (p == k) {
								s += j + '0';
							}
							else {
								s += l + '0';
							}
							continue;
						}
						if (p == k) {
							s += l + '0';
						}
						else {
							s += j + '0';
						}
					}
					ll sl = stoll(s);
					if (sl >= al && sl <= bl) {
						moos++;
					}
				}
			}
		}
	}
	return moos;
}

int main() {
	ifstream fin("odometer.in");
	ofstream fout("odometer.out");
	
	fin >> X >> Y;

	int total = findmoos(X, Y);

	fout << total << '\n';
}