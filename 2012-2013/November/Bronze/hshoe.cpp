#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int N, maxLen = 0;
char grid[5][5];

bool invalid(vector<char>& s) {
	int ls = 0;
	while (ls < s.size() && s[ls] == '(') {
		ls++;
	}
	if (s.size() - ls > ls) {
		return true;
	}
	for (int i = ls; i < s.size(); i++) {
		if (s[i] == '(') {
			return true;
		}
	}
	return false;
}

bool perf(vector<char>& s) {
	int ls = 0;
	while (ls < s.size() && s[ls] == '(') {
		ls++;
	}
	if (s.size() - ls != ls) {
		return false;
	}
	for (int i = ls; i < s.size(); i++) {
		if (s[i] == '(') {
			return false;
		}
	}
	return true;
}

void findPaths(int x, int y, vector<char>& s, vector<vector<bool>>& visited, int move) {
	s.push_back(grid[x][y]);
	visited[x][y] = true;
	if (perf(s)) {
		if (s.size() > maxLen) {
			maxLen = s.size();
		}
		visited[x][y] = false;
		s.pop_back();
		return;
	}
	if (!invalid(s)) {
		if (x > 0) {
			if (!visited[x - 1][y]) {
				findPaths(x - 1, y, s, visited, move + 1);
			}
		}
		if (x < N - 1) {
			if (!visited[x + 1][y]) {
				findPaths(x + 1, y, s, visited, move + 1);
			}
		}
		if (y > 0) {
			if (!visited[x][y - 1]) {
				findPaths(x, y - 1, s, visited, move + 1);
			}
		}
		if (y < N - 1) {
			if (!visited[x][y + 1]) {
				findPaths(x, y + 1, s, visited, move + 1);
			}
		}
	}
	visited[x][y] = false;
	s.pop_back();
}

int main() {
	ifstream fin("input.in");
	fin >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			fin >> grid[i][j];
		}
	}

	vector<char> s;
	vector<vector<bool>> visited(5, vector<bool>(5, false));
	findPaths(0, 0, s, visited, 1);

	cout << maxLen;
}