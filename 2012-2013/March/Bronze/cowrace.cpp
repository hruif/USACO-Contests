#include <iostream>
#include <fstream>

using namespace std;

int N, M;
int B[1000][2];
int E[1000][2];

int main() {
	ifstream fin("cowrace.in");
	fin >> N >> M;
	for (int i = 0; i < N; i++) {
		fin >> B[i][0] >> B[i][1];
	}
	for (int i = 0; i < M; i++) {
		fin >> E[i][0] >> E[i][1];
	}
	int start = B[0][0] > E[0][0] ? 1 : -1;
	int count = 0;
	int time = 0;
	int bc = 0, ec = 0;
	int bp = 0, ep = 0;
	while (bp != N || ep != M) {
		if (B[bp][1] == 0) {
			bp++;
		}
		if (E[ep][1] == 0) {
			ep++;
		}
		if (bp != N) {
			bc += B[bp][0];
			B[bp][1]--;
		}
		if (ep != M) {
			ec += E[ep][0];
			E[ep][1]--;
		}
		if (bc > ec && start == -1) {
			start = 1;
			count++;
		}
		if (ec > bc && start == 1) {
			start = -1;
			count++;
		}
	}
	ofstream fout("cowrace.out");
	fout << count << '\n';
}