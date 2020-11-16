#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int N, a, b;
int mirrors[500][3];
vector<vector<int>> rows;
vector<vector<int>> cols;

int newDir(int dirIn, int mir) {
	if (mir == 0) {
		switch (dirIn) {
		case 0:
			return 1;
		case 1:
			return 0;
		case 2:
			return 3;
		case 3:
			return 2;
		}
	}
	else {
		switch (dirIn) {
		case 0:
			return 3;
		case 1:
			return 2;
		case 2:
			return 1;
		case 3:
			return 0;
		}
	}
}

bool reaches(int mirflip) {
	if (mirflip != -1) {
		mirrors[mirflip][2] = abs(mirrors[mirflip][2] - 1);
	}

	int x = 0, y = 0;
	int dir = 1;
	while (true) {
		if (dir == 0) {
			
		}
	}

	if (mirflip != -1) {
		mirrors[mirflip][2] = abs(mirrors[mirflip][2] - 1);
	}
}

int main() {
	ifstream fin("input.in");
	fin >> N >> a >> b;
	for (int i = 0; i < N; i++) {
		char dir;
		cin >> mirrors[i][0] >> mirrors[i][1] >> dir;
		if (dir == '\\') {
			mirrors[i][2] = 0;
		}
		else {
			mirrors[i][2] = 1;
		}
		bool found = false;
		for (int j = 0; j < rows.size(); j++) {
			if (mirrors[i][0] == mirrors[rows[j][0]][0]) {
				rows[j].push_back(i);
				found = true;
				break;
			}
		}
		if (!found) {
			rows.push_back(vector<int>());
			rows[rows.size() - 1].push_back(i);
		}
		found = false;
		for (int j = 0; j < cols.size(); j++) {
			if (mirrors[i][1] == mirrors[cols[j][0]][1]) {
				cols[j].push_back(i);
				found = true;
				break;
			}
		}
		if (!found) {
			cols.push_back(vector<int>());
			cols[cols.size() - 1].push_back(i);
		}
	}
	int mir = 0;
	while (!reaches(mir)) {
		mir++;
	}
	if (mir == N) {
		mir = -2;
	}
	cout << mir + 1;
}