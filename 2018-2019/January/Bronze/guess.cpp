#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_set>
#include <algorithm>

using namespace std;

int N;
int yess[100];
vector<string> ac[100];
unordered_set<string> chars;

int main() {
	ifstream fin("guess.in");
	ofstream fout("guess.out");

	fin >> N;
	for (int i = 0; i < N; i++) {
		string name;
		int K;
		fin >> name >> K;
		for (int j = 0; j < K; j++) {
			string c;
			fin >> c;
			ac[i].push_back(c);
		}
	}
	
	int maxyess = 0;
	for (int i = 0; i < N - 1; i++) {
		chars.clear();

		int size = ac[i].size();
		for (int j = 0; j < ac[i].size(); j++) {
			chars.insert(ac[i][j]);
		}

		for (int j = i + 1; j < N; j++) {
			int shared = 0;
			int asize = ac[j].size();
			for (int k = 0; k < ac[j].size(); k++) {
				string& s = ac[j][k];
				if (chars.find(s) != chars.end()) shared++;
			}
			int yess = min(shared + 1, max(size, asize));
			maxyess = max(yess, maxyess);
		}
	}
	fout << maxyess << '\n';
}