#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

int N;
int nextC[1000];

bool visited[1000];
bool loopy(int c) {
	memset(visited, false, sizeof(visited));
	visited[c] = true;
	while (nextC[c] != 0 && !visited[nextC[c] - 1]) {
		c = nextC[c] - 1;
		visited[c] = true;
	}
	return nextC[c] != 0;
}

int main() {
	ifstream fin("relay.in");
	fin >> N;
	for (int i = 0; i < N; i++) {
		fin >> nextC[i];
	}
	int total = 0;
	for (int i = 0; i < N; i++) {
		if (!loopy(i)) {
			total++;
		}
	}
	ofstream fout("relay.out");
	fout << total << '\n';
}