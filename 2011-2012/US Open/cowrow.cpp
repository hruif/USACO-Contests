#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

struct Group {
	int ID;
	int pop;
	Group() {
		ID = -1;
		pop = 0;
	}
	Group(int ID, int pop) {
		this->ID = ID;
		this->pop = pop;
	}
};

int N;
int B[1000];
vector<Group> groups;

int main() {
	ifstream fin("input.in");
	fin >> N;
	fin >> B[0];
	groups.push_back(Group(B[0], 1));
	int last = 0;
	for (int i = 1; i < N; i++) {
		fin >> B[i];
		if (B[i] == groups[last].ID) {
			groups[last].pop++;
		}
		else {
			groups.push_back(Group(B[i], 1));
			last++;
		}
	}
	int maxPop = groups[groups.size() - 1].pop;
	for (int i = 0; i < groups.size() - 1; i++) {
		int ID = groups[i].ID;
		int removeID = groups[i + 1].ID;
		int pop = groups[i].pop;
		for (int j = i + 2; j < groups.size(); j += 2) {
			if (groups[j - 1].ID != removeID || groups[j].ID != ID) {
				break;
			}
			pop += groups[j].pop;
		}
		if (pop > maxPop) {
			maxPop = pop;
		}
	}
	cout << maxPop;
}