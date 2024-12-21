#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int A[100000];
vector<int> st;
vector<vector<int>> cnts;

void addto(int k) {
    int sn = st.size() / 2;
    k += sn;
    st[k]++;
    for (k /= 2; k >= 1; k /= 2) st[k] = st[k * 2] + st[k * 2 + 1];
}

int findsum(int a, int b) {
    int sn = st.size() / 2;
    a += sn; b += sn;
    int sum = 0;
    while (a <= b) {
        if (a % 2 == 1) sum += st[a++];
        if (b % 2 == 0) sum += st[b--];
        a /= 2; b /= 2;
    }
    return sum;
}

void setst(int n) {
    int sn = 1;
    while (sn < n) sn *= 2; 
    st.resize(sn * 2, 0);
}

int main() {
    ifstream fin("haircut.in");
    ofstream fout("haircut.out");
    //ifstream fin("input.txt");
    //ofstream fout("output.txt");

    int N;
    fin >> N;
    cnts.resize(N + 1);
    for (int i = 0; i < N; i++) fin >> A[i];
    for (int i = 0; i < N; i++) cnts[A[i]].push_back(i);
    setst(N);

    long long cnt = 0;
    for (int i = 0; i < N; i++) {
        fout << cnt << '\n';
        for (int j = 0; j < cnts[i].size(); j++) {
            cnt += cnts[i][j] - findsum(0, cnts[i][j] - 1);
            addto(cnts[i][j]);
        }
    }
}