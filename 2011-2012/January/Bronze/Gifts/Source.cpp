/*
ID: ruifanl1
TASK: gifts
LANG: C++
*/

#include <iostream>
#include <fstream>

using namespace std;

int N, B;
int P[1000];
int S[1000];
int main() {
	ifstream fin("gifts.in");
	fin >> N >> B;
	for (int i = 0; i < N; i++) {
		fin >> P[i] >> S[i];
	}

	for (int i = 0; i < N - 1; i++) {
		int isum = P[i] + S[i];
		for (int j = i + 1; j < N; j++) {
			int jsum = P[j] + S[j];
			if (isum > jsum) {
				int tmp = P[i];
				P[i] = P[j];
				P[j] = tmp;
				tmp = S[i];
				S[i] = S[j];
				S[j] = tmp;
				isum = S[i] + P[i];
			}
		}
	}

	int count = 0;
	int end = 0;
	long long cost = 0;
	while (end < N) {
		cost += P[end] + S[end];
		if (cost > B) {
			cost -= P[end] + S[end];
			break;
		}
		end++;
		count++;
	}

	int ans = count;
	ofstream fout("gifts.out");
	if (end != N) {
		int maxAdd = 0;
		for (int i = 0; i < N; i++) {
			long long tmpCost;
			if (i < end) {
				tmpCost = cost - P[i] / 2;
				tmpCost += P[end] + S[end];
			}
			else {
				tmpCost = cost + P[i] / 2 + S[i];
			}
			int tmpMAdd = 0;
			int pos = i <= end ? end + 1 : end;
			while (tmpCost <= B) {
				tmpMAdd++;
				if (pos == i) {
					pos++;
				}
				tmpCost += P[pos] + S[pos];
				pos++;
			}
			if (tmpMAdd > maxAdd) {
				maxAdd = tmpMAdd;
			}
		}
		ans += maxAdd;
	}
	fout << ans << '\n';
}