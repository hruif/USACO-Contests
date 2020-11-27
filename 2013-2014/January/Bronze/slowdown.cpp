#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

int N;
int Ts[10000];
int Ds[10000];
int speeds[10001];

int main() {
	ifstream fin("slowdown.in");
	fin >> N;
	int nt = 0, nd = 0; // num of ts, num of ds
	for (int i = 0; i < N; i++) {
		char ev;
		fin >> ev;
		if (ev == 'T') {
			fin >> Ts[nt++];
		}
		else {
			fin >> Ds[nd++];
		}
	}
	sort(Ts, Ts + nt);
	sort(Ds, Ds + nd);
	int slow = 1;
	double time = 0;
	double dist = 0;
	const double o = 1;
	int pt = 0, pd = 0; // t pointer, d pointer
	while (pt != nt || pd != nd) {
		if (pt == nt) {
			double dif = Ds[pd++] - dist;
			time += dif / (o / slow);
			dist += dif;
			slow++;
		}
		else if (pd == nd) {
			double dif = Ts[pt++] - time;
			dist += dif * (o / slow);
			time += dif;
			slow++;
		}
		else {
			int nextt = Ts[pt];
			int nextd = Ds[pd];
			double tdif = nextt - time;
			double ddif = nextd - dist;
			double ttd = tdif * (o / slow); // time to distance
			ttd += dist;
			double dtt = ddif / (o / slow); // distance to time
			dtt += time;
			if (ttd < nextd) {
				pt++;
				dist = ttd;
				time += tdif;
			}
			else {
				time = dtt;
				dist += ddif;
				pd++;
			}
			slow++;
		}
	}
	double totaltime = (1000 - dist) / (o / slow) + time;
	int inttime = totaltime;
	if (totaltime - inttime >= 0.5) {
		inttime++;
	}
	ofstream fout("slowdown.out");
	fout << inttime << '\n';
}