#include <iostream>
#include <fstream>
#include <vector>

#define ll long long

using namespace std;

#ifdef LOCAL_DEBUG
ifstream fin("input.txt");
ofstream fout("output.txt");
#else
#define fin cin
#define fout cout
#endif

int Q;

int main() {
    fin >> Q;
    while (Q--) {
        ll d, x, y;
        fin >> d >> x >> y;
        ll v = 1, p = 0;
        for (int i = 0; i < 30; i++) {
            v *= 3; p++;
        }
        fout << v << ' ' << p;
    }
}