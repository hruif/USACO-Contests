#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

int N;
int points[100000][2];
int cuts[100000];

int main() {
	ifstream fin("marathon.in");
	ofstream fout("marathon.out");
	
	fin >> N;
	for (int i = 0; i < N; i++) {
		fin >> points[i][0] >> points[i][1];
	}
	for (int i = 1; i < N - 1; i++) {
		int normdist = abs(points[i][0] - points[i - 1][0]) + abs(points[i][1] - points[i - 1][1]) + 
			abs(points[i][0] - points[i + 1][0]) + abs(points[i][1] - points[i + 1][1]);
		int skipdist = abs(points[i + 1][0] - points[i - 1][0]) + abs(points[i + 1][1] - points[i - 1][1]);
		cuts[i] = normdist - skipdist;
	}
	int dist = 0;
	for (int i = 1; i < N; i++) {
		dist += abs(points[i][0] - points[i - 1][0]) + abs(points[i][1] - points[i - 1][1]);
	}
	int maxcut = 0;
	for (int i = 1; i < N - 1; i++) {
		maxcut = max(maxcut, cuts[i]);
	}
	fout << dist - maxcut << '\n';
}