#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

#ifdef LOCAL_DEBUG
ifstream fin("input.txt");
ofstream fout("output.txt");
#else
ifstream fin("input.txt");
ofstream fout("output.txt");
#endif

int N;
int A[100000];

int main() {
    //fin >> N;
    //for (int i = 0; i < N; i++) fin >> A[i];

    N = rand() % 10 + 1;
    for (int i = 0; i < N; i++) {
        A[i] = rand() % (N * 2) + 1;
        fout << A[i] << ' ';
    }
    fout << '\n';
    bool sorted = false;
    while (!sorted) {
        sorted = true;
        fout << "moo\n";
        for (int i = 0; i < N - 1; i++) {
            if (A[i + 1] < A[i]) swap(A[i + 1], A[i]);
        }
        for (int i = N - 2; i >= 0; i--) {
            if (A[i + 1] < A[i]) swap(A[i + 1], A[i]);
        }
        for (int i = 0; i < N - 1; i++) {
            if (A[i + 1] < A[i]) sorted = false;
        }
    }
}