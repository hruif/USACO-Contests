#include <iostream>
#include <vector>

using namespace std;

int N;
int points[10][2];
vector<int> visitable[10][4];

int findPaths(bool* visited, int on, int dir) {
	bool allVisited = true;
	for (int i = 0; i < N; i++) {
		if (!visited[i]) {
			allVisited = false;
			break;
		}
	}
	if (allVisited) {
		return 1;
	}

	int paths = 0;
	for (int i = 0; i < 4; i++) {
		if (i == dir) {
			continue;
		}
		for (int j = 0; j < visitable[on][i].size(); j++) {
			int next = visitable[on][i][j];
			if (visited[next]) {
				continue;
			}
			visited[next] = true;
			paths += findPaths(visited, next, i);
			visited[next] = false;
		}
	}
	return paths;
}

int main() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> points[i][0] >> points[i][1];
		for (int j = 0; j < i; j++) {
			if (points[j][0] == points[i][0]) {
				if (points[j][1] < points[i][1]) {
					visitable[j][0].push_back(i);
					visitable[i][2].push_back(j);
				}
				else {
					visitable[j][2].push_back(i);
					visitable[i][0].push_back(j);
				}
			}
			if (points[j][1] == points[i][1]) {
				if (points[j][0] < points[i][0]) {
					visitable[j][1].push_back(i);
					visitable[i][3].push_back(j);
				}
				else {
					visitable[j][3].push_back(i);
					visitable[i][1].push_back(j);
				}
			}
		}
	}
	bool visited[10];
	for (int i = 0; i < 10; i++) {
		visited[i] = false;
	}
	int ans = 0;
	for (int i = 0; i < N; i++) {
		if (points[i][0] == 0 || points[i][1] == 0) {
			int dir;
			if (points[i][1] > 0) {
				dir = 0;
			}
			if (points[i][0] > 0) {
				dir = 1;
			}
			if (points[i][1] < 0) {
				dir = 2;
			}
			if (points[i][0] < 0) {
				dir = 3;
			}
			visited[i] = true;
			ans += findPaths(visited, i, dir);
			visited[i] = false;
		}
	}
	cout << ans;
}