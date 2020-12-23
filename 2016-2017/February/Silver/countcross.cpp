#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

int N, K, R;
int cows[100][2];
int dis[100][100][4];
bool cow[100][100];

bool visited[100][100];

int findpairs(int x, int y) {
	if (visited[x][y]) return 0;
	visited[x][y] = true;

	int pairs = 0;
	if (cow[x][y]) pairs++;
	if (!dis[x][y][0] && y < N - 1) pairs += findpairs(x, y + 1);
	if (!dis[x][y][1] && x < N - 1) pairs += findpairs(x + 1, y);
	if (!dis[x][y][2] && y > 0) pairs += findpairs(x, y - 1);
	if (!dis[x][y][3] && x > 0) pairs += findpairs(x - 1, y);

	return pairs;

}

int main() {
	ifstream fin("countcross.in");
	ofstream fout("countcross.out");

	fin >> N >> K >> R;
	for (int i = 0; i < N; i++) {
		int x1, y1, x2, y2;
 		fin >> x1 >> y1 >> x2 >> y2;
		x1--, y1--, x2--, y2--;
		if (x1 < x2) {
			dis[x1][y1][1] = true;
			dis[x2][y2][3] = true;
		}
		else if (x1 > x2) {
			dis[x1][y1][3] = true;
			dis[x2][y2][1] = true;
		}
		else if (y1 < y2) {
			dis[x1][y1][0] = true;
			dis[x2][y2][2] = true;
		}
		else {
			dis[x1][y1][2] = true;
			dis[x2][y2][0] = true;
		}
	}
	for (int i = 0; i < K; i++) {
		fin >> cows[i][0] >> cows[i][1];
		cows[i][0]--, cows[i][1]--;
		cow[cows[i][0]][cows[i][1]] = true;
	}

	int pairs = 0;
	for (int i = 0; i < K; i++) {
		memset(visited, false, sizeof(visited));
		int x = cows[i][0];
		int y = cows[i][1];
		cow[x][y] = false;
		pairs += K - 1 - findpairs(x, y);
		cow[x][y] = true;
	}

	fout << pairs / 2 << '\n';
}