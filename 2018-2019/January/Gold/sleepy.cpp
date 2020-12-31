#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int N, treen = 1;
int arr[100000];
vector<int> segtr;
int comms[100000];

void updsegtr(int k) {
	k += treen;
	segtr[k] = 1;
	for (k /= 2; k >= 1; k /= 2) {
		segtr[k] = segtr[k * 2] + segtr[k * 2 + 1];
	}
}

int find1s(int a) {
	a += treen;
	int b = N - 1 + treen;
	int s = 0;
	while (a <= b) {
		if (a % 2 == 1) s += segtr[a++];
		if (b % 2 == 0) s += segtr[b--];
		a /= 2, b /= 2;
	}
	return s;
}

int main() {
	ifstream fin("sleepy.in");
	ofstream fout("sleepy.out");
	
	fin >> N;
	for (int i = 0; i < N; i++) {
		fin >> arr[i];
		arr[i]--;
	}

	while (treen < N) {
		treen *= 2;
	}
	segtr.resize(treen * 2);
	int last = N - 1;
	for (int i = N - 2; i >= 0; i--) {
		if (arr[i] > arr[i + 1]) break;
		last = i;
	}
	fout << last << '\n';
	for (int i = last - 1; i >= 0; i--) {
		int num = arr[i];
		comms[i] = num + find1s(num);
		updsegtr(arr[i]);
	}
	if (last > 0) {
		for (int i = 0; i < last; i++) {
			if (i != 0) fout << ' ';
			fout << comms[i];
		}
		fout << '\n';
	}
}