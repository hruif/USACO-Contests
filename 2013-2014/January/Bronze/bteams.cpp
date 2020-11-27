#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

int skills[12];
int mindif = -1;
int ts[4];

bool visited[12];
void makeTeams(int tstart, int pms, int m, int t) {
	if (m == 3) {
		m = 0;
		t++;
		pms = tstart;
	}
	if (t == 4) {
		int max = 0;
		for (int i = 0; i < 3; i++) {
			for (int j = i + 1; j < 4; j++) {
				int dif = abs(ts[i] - ts[j]);
				if (dif > max) {
					max = dif;
				}
			}
		}
		if (max < mindif || mindif == -1) {
			mindif = max;
		}
		return;
	}

	for (int i = pms + 1; i < 12; i++) {
		if (!visited[i]) {
			ts[t] += skills[i];
			visited[i] = true;
			if (m == 0) {
				tstart = i;
			}
			makeTeams(tstart, i, m + 1, t);
			visited[i] = false;
			ts[t] -= skills[i];
		}
	}
}

int main() {
	ifstream fin("bteams.in");
	for (int i = 0; i < 12; i++) {
		fin >> skills[i];
	}
	sort(skills, skills + 12);
	int l = 0, r = 11;
	makeTeams(-1, -1, 0, 0);

	ofstream fout("bteams.out");
	fout << mindif << '\n';
}