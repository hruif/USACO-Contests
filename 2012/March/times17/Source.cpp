#include <iostream>

using namespace std;

char N[1000];
char revN[1000];
char N16[1004];
char out[1004];

int main() {
	cin >> N;
	int end = 1000;
	for (int i = 999; i >= 0; i--) {
		if (N[i]) {
			break;
		}
		end = i;
	}
	for (int i = 0; i < end; i++) {
		revN[i] = N[end - i - 1];
	}
	N16[0] = '0';
	N16[1] = '0';
	N16[2] = '0';
	N16[3] = '0';
	for (int i = 0; i < end; i++) {
		N16[i + 4] = revN[i];
	}
	for (int i = 0; i < 4; i++) {
		out[i] = revN[i];
	}
	bool carry = false;
	for (int i = 4; i < end; i++) {
		int a = 0;
		bool N1 = revN[i] == '1';
		bool N161 = N16[i] == '1';
		if (N1) {
			a++;
		}
		if (N161) {
			a++;
		}
		if (carry) {
			a++;
			carry = false;
		}
		if (a % 2 == 1) {
			out[i] = '1';
		}
		else {
			out[i] = '0';
		}
		if (a >= 2) {
			carry = true;
		}
	}
	for (int i = end; i < end + 4; i++) {
		int a = 0;
		if (N16[i] == '1') {
			a++;
		}
		if (carry) {
			a++;
			carry = false;
		}
		if (a == 1) {
			out[i] = '1';
		}
		else {
			if (a == 2) {
				carry = true;
			}
			out[i] = '0';
		}
	}
	if (carry) {
		cout << '1';
	}
	for (int i = end + 4 - 1; i >= 0; i--) {
		cout << out[i];
	}
	cout << '\n';
}