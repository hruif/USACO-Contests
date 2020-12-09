#include <iostream>
#include <fstream>
#include <string>

using namespace std;

string S, T;

int main() {
    ifstream fin("censor.in");
    ofstream fout("censor.out");

    fin >> S >> T;
    size_t dfd;

    int ns = T.size();
    int ssize = S.size();
    for (int i = 0; i < S.size() - ns; i++) {
        if (i < 0) continue;

        string sT = S.substr(i, ns);
        if (S.substr(i, ns) == T) {
            S.erase(i, ns);
            ssize -= ns;
            i -= ns;
        }
    }

    fout << S << '\n';
}