#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int N, K;
int ics[100000];
vector<int> cs;
vector<vector<int>> con;

int main() {
	ifstream fin("barnpainting.in");
	ofstream fout("barnpainting.out");

	fin >> N >> K;
	cs.resize(N, 7);
	for (int i = 0; i < N; i++) {
		int a, b;
		cin >> a >> b;
		a--, b--;
		con[a].push_back(b);
		con[b].push_back(a);
	}
	for (int i = 0; i < K; i++) {
		int b, c;
		fin >> b >> c;
		b--, c--;
		cs[b] <<= c;
	}

	for (int i = 0; i < 
}