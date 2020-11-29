#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

struct Word {
	string w;
	int ind;
	bool operator<(const Word a) const {
		return w < a.w;
	}
	Word() {}
	Word(string w, int ind) {
		this->w = w;
		this->ind = ind;
	}
};

int W, N;
vector<Word> dict;

int searchstart(string word) {
	int l = 0, r = W;
	while (l < r) {
		int mid = (l + r) / 2 + 1;
		if (dict[mid].w >= word) {
			r = mid - 1;
		}
		else {
			l = mid;
		}
	}
	return l;
}

int main() {
	ifstream fin("auto.in");
	fin >> W >> N;
	string t = "";
	dict.push_back(Word(t, 0));
	for (int i = 0; i < W; i++) {
		string word;
		fin >> word;
		dict.push_back(Word(word, i + 1));
	}
	sort(dict.begin(), dict.end());

	ofstream fout("auto.out");
	for (int i = 0; i < N; i++) {
		int K;
		string word;
		fin >> K >> word;
		int p = searchstart(word);
		p++;
		int c = 0;
		while (p < W && dict[p].w.substr(0, word.size()) == word && c < K) {
			c++;
			p++;
		}
		if (c < K) {
			fout << "-1\n";
		}
		else {
			fout << dict[p - 1].ind << '\n';
		}
	}
}