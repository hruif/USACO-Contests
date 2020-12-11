#include <iostream>
#include <fstream>
#include <utility>
#include <unordered_map>

using namespace std;

int N;
unordered_map<long long, int> visited;

int main() {
	ifstream fin("mowing.in");
	ofstream fout("mowing.out");
	
	fin >> N;
	int x = 0, y = 0;
	int mint = 1000000000;
	int t = 0;
	for (int i = 0; i < N; i++) {
		char dir;
		int dis;
		fin >> dir >> dis;
		for (int j = 0; j < dis; j++) {
			if (dir == 'N') y++;
			else if (dir == 'E') x++;
			else if (dir == 'S') y--;
			else if (dir == 'W') x--;
			t++;
			long long lx = x, ly = y;
			long long s = (lx << 32) + ly;
			if (visited.find(s) == visited.end()) visited[s] = t;
			else {
				int tp = t - visited[s];
				if (tp < mint) mint = tp;
				visited[s] = t;
			}
		}
	}
	if (mint == 1000000000) mint = -1;
	fout << mint << '\n';
}