#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int N, M;
char a[1000][1000];
int cnt = 0;
int maxcnt = -2;

void reflect(int r, int c, int dir) {
    if (cnt > M * N) {
        maxcnt = -1;
        return;
    }
    if (r < 0 || r >= N || c < 0 || c >= M) {
        if (cnt > maxcnt) {
            maxcnt = cnt;
        }
        return;
    }
    if (dir == 0) {
        if (a[r][c] == '/') {
            cnt++;
            reflect(r - 1, c, 3);
            if (maxcnt == -1) return;
            cnt--;
        }
        else if (a[r][c] == '\\') {
            cnt++;
            reflect(r + 1, c, 1);
            if (maxcnt == -1) return;
            cnt--;
        }
    }
    else if (dir == 1) {
        if (a[r][c] == '/') {
            cnt++;
            reflect(r, c - 1, 2);
            if (maxcnt == -1) return;
            cnt--;
        }
        else if (a[r][c] == '\\') {
            cnt++;
            reflect(r, c + 1, 0);
            if (maxcnt == -1) return;
            cnt--;
        }
    }
    else if (dir == 2) {
        if (a[r][c] == '/') {
            cnt++;
            reflect(r + 1, c, 1);
            if (maxcnt == -1) return;
            cnt--;
        }
        else if (a[r][c] == '\\') {
            cnt++;
            reflect(r - 1, c, 3);
            if (maxcnt == -1) return;
            cnt--;
        }
    }
    else if (dir == 3) {
        if (a[r][c] == '/') {
            cnt++;
            reflect(r, c + 1, 0);
            if (maxcnt == -1) return;
            cnt--;
        }
        else if (a[r][c] == '\\') {
            cnt++;
            reflect(r, c - 1, 2);
            if (maxcnt == -1) return;
            cnt--;
        }
    }
}

int main() {
    ifstream fin("mirror.in");
    ofstream fout("mirror.out");

    fin >> N >> M;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            fin >> a[i][j];
        }
    }

    for (int i = 0; i < N; i++) {
        // left
        reflect(i, 0, 0);
        if (maxcnt == -1) break;
        // right
        reflect(i, M - 1, 2);
    }
    for (int i = 0; i < M; i++) {
        if (maxcnt == -1) break;
        // top
        reflect(0, i, 1);
        if (maxcnt == -1) break;
        // bottom
        reflect(N - 1, i, 3);
    }
    fout << maxcnt << endl;
}