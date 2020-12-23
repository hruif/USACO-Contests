#include <iostream>
#include <algorithm>
using namespace std;

int nums[7];

int main() {
	for (int i = 0; i < 7; i++) {
		cin >> nums[i];
	}
	sort(nums, nums + 7);
	int A, B, C;
	A = nums[0];
	B = nums[1];
	C = nums[6] - A - B;
	cout << A << ' ' << B << ' ' << C << '\n';
}