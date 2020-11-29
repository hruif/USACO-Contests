#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int total = 0;

void solve(string s0) {
    int l = s0.size();
    if (l < 3 || l % 2 == 0) return;
    int h = l / 2;
    {
        string s = s0.substr(0, h + 1);
        string t = s0.substr(h + 1);
        if (s == t + s[h] || s == s[0] + t) {
            total++;
            solve(s);
        }
    }
    {
        string s = s0.substr(h);
        string t = s0.substr(0, h);
        if (s == t + s[h] || s == s[0] + t) {
            total++;
            solve(s);
        }
    }
}

int main() {
    ifstream fin("scode.in");
    ofstream fout("scode.out");

    string s;
    fin >> s;

    solve(s);
    fout << total << endl;
}