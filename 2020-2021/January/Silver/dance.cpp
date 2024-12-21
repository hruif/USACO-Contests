#include <iostream>
#include <fstream>
#include <vector>
#include <set>

using namespace std;

#ifdef LOCAL_DEBUG
ifstream fin("input.txt");
ofstream fout("output.txt");
#else
#define fin cin
#define fout cout
#endif

int N, K;
vector<int> b;
vector<set<int>> Ss;

int main() {
    fin >> N >> K;
    b.resize(K);
}