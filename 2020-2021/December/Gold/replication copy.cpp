#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <utility>
#include <string.h>
#include <algorithm>

using namespace std;

#define fi first
#define se second
#define pii pair<int, int>

//#define LOCALL

#ifdef LOCALL
ifstream fin("input.txt");
ofstream fout("output.txt");
#else
#define fin cin
#define fout cout
#endif

long long N, D;
vector<vector<char>> grid;
vector<vector<int>> dist_to_rock;
vector<vector<bool>> can_center;
vector<vector<bool>> can_visit;

int main() {
    fin >> N >> D;
    grid.resize(N, vector<char>(N));
    dist_to_rock.resize(N, vector<int>(N, -1));
    can_center.resize(N, vector<bool>(N, false));
    can_visit.resize(N, vector<bool>(N, false));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            fin >> grid[i][j];
        }
    }
    
    queue<pair<pii, int>> nodes;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (grid[i][j] == '#') {
                dist_to_rock[i][j] = 0;
                nodes.push({  {  i, j  }, 0  });
            }
        }
    }
    while (!nodes.empty()) {
        pair<pii, int> node = nodes.front();
        nodes.pop();

        int i = node.first.first, j = node.first.second;
        int ndist = node.second + 1;
        if (i > 0 && dist_to_rock[i - 1][j] == -1) {
            dist_to_rock[i - 1][j] = ndist;
            nodes.push({  {  i - 1, j  }, ndist  });
        }            
        if (i < N - 1 && dist_to_rock[i + 1][j] == -1) {
            dist_to_rock[i + 1][j] = ndist;
            nodes.push({  {  i + 1, j  }, ndist  });
        }
        if (j > 0 && dist_to_rock[i][j - 1] == -1) {
            dist_to_rock[i][j - 1] = ndist;
            nodes.push({  {  i, j - 1  }, ndist  });
        }
        if (j < N - 1 && dist_to_rock[i][j + 1] == -1) {
            dist_to_rock[i][j + 1] = ndist;
            nodes.push({  {  i, j + 1  }, ndist  });
        }
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (grid[i][j] == 'S') {
                nodes.push({  {  i, j  }, 0  });
            }
        }
    }
    while (!nodes.empty()) {
        pair<pii, int> node = nodes.front();
        nodes.pop();

        int i = node.first.first, j = node.first.second;
        long long hours = node.second;
        int reps = hours / D;
        if (can_center[i][j]) continue;
        if (hours > D * dist_to_rock[i][j]) continue;
        can_center[i][j] = true;
        if (hours >= D * dist_to_rock[i][j]) continue;
        if (i > 0) nodes.push({  {  i - 1, j  }, hours + 1  });
        if (i < N - 1) nodes.push({  {  i + 1, j  }, hours + 1  });
        if (j > 0) nodes.push({  {  i, j - 1  }, hours + 1  });
        if (j < N - 1) nodes.push({  {  i, j + 1  }, hours + 1  });
    }

    vector<pair<int, pii>> centers;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (can_center[i][j]) centers.push_back({  dist_to_rock[i][j],
                {  i, j  }  });
        }
    }
    sort(centers.begin(), centers.end());

    int p = centers.size() - 1;
    int maxreps = N;
    queue<pair<pii, int>> to_visit;
    while (p >= 0) {
        while (p >= 0 && centers[p].first == maxreps) {
            to_visit.push({  {  centers[p].second.first, 
                centers[p].second.second  }, centers[p].first  });
            p--;
        }
        while (!to_visit.empty() && to_visit.front().second == maxreps) {
            pair<pii, int> node = to_visit.front();
            to_visit.pop();

            int i = node.first.first, j = node.first.second;
            int dist = node.second;
            if (can_visit[i][j] || grid[i][j] == '#' || dist < 0) continue;
            can_visit[i][j] = true;
            if (i > 0) to_visit.push({  {  i - 1, j  }, dist - 1  });
            if (i < N - 1) to_visit.push({  {  i + 1, j  }, dist - 1  });
            if (j > 0) to_visit.push({  {  i, j - 1  }, dist -  1  });
            if (j < N - 1) to_visit.push({  {  i, j + 1  }, dist - 1  });
        }
        maxreps--;
    }
    
    int cnt = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (can_visit[i][j]) cnt++;
        }
    }
    fout << cnt << '\n';
}