#include <iostream>
#include <fstream>
#include <vector>
#include <set>

using namespace std;

ifstream fin("248.in");
ofstream fout("248.out");
//ifstream fin("input.txt");
//ofstream fout("output.txt");

int N;
vector<long long> si, pr;
long long maxval;
set<long long> vis;

long long exp(int b, int e) {
    if (e == 0) return 1;
    long long val = exp(b, e / 2);
    val *= val;
    if (e % 2) val *= b;
    return val % 1000000007;
}

void testS(vector<long long> s) {
    long long hash = 1; 
    for (int i = 0; i < s.size(); i++) {
        hash *= exp(pr[i], s[i]);
        hash %= 1000000007;
    }
    if (vis.find(hash) != vis.end()) return;
    vis.insert(hash);
    for (int i =  0; i < s.size() - 1; i++) {
        maxval = max(maxval, s[i]);
        if (s[i] == s[i + 1]) {
            vector<long long> ns = s;
            ns.erase(ns.begin() + i);
            ns[i]++;
            testS(ns);
        }
    }
    maxval = max(maxval, s[s.size() - 1]);
}

int main() {
    for (int i = 3; i < 10000; i += 2) {
        bool np = false;
        for (int j = 0; j < pr.size(); j++) {
            if (i % pr[j] == 0) np = true;
        }
        if (np) continue;
        pr.push_back(i);
    }
    while (pr[0] <= 40) pr.erase(pr.begin());

    fin >> N;
    si.resize(N);
    for (int i = 0; i < N; i++) fin >> si[i];
    for (int i = 0; i < N; i++) maxval = max(maxval, si[i]);
    testS(si);
    fout << maxval << '\n';
}