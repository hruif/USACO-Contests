#include <iostream>
#include <fstream>
#include <unordered_map>

using namespace std;

int N, K;
unordered_map<int, int> nums;

int main() {
	ifstream fin("proximity.in");
	fin >> N >> K;
	int max = 0;
	for (int i = 0; i < N; i++) {
		int num;
		fin >> num;
		if (nums.find(num) != nums.end()) {
			if (i - nums[num] <= K) {
				if (num > max) {
					max = num;
				}
			}
		}
		nums[num] = i;
	}
	ofstream fout("proximity.out");
	fout << max << '\n';
}