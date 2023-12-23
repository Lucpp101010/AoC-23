#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int)size(x)

constexpr int inf = 1e8;

vector<int> di = {-1, 0, 1, 0};
vector<int> dj = {0, 1, 0, -1};

int n, m;
vector<string> grid;
vector<vector<pair<int, int>>> g;
vector<bool> vis, vis2;
map<pair<int, vector<bool>>, int> cache;

void dfs(int v){
    vis2[v] = true;
    for(auto [u, d] : g[v]){
        if(!vis2[u]) dfs(u);
    }
}

bool check(int v){
    vis2 = vis;
    dfs(v);
    return vis2[1];
}

int calc(int v){
    if(v == 1) return 0;
    if(cache.contains({v, vis})){
        return cache[{v, vis}];
    }
    int len = -inf;
    vis[v] = true;
    for(auto [u, d] : g[v]){
        if(vis[u]) continue;
        if(!check(u)) continue;
        len = max(len, d + calc(u));
    }
    vis[v] = false;
    return cache[{v, vis}] = len;
}

int main(){
    string line;
    while(cin >> line) grid.push_back(line);
    n = sz(grid), m = sz(grid[0]);
    vector<vector<int>> vertId(n, vector<int>(m, -1));
    vertId[0][1] = 0;
    vertId[n-1][m-2] = 1;
    int nextId = 2;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if(grid[i][j] == '#') continue;
            int deg = 0;
            for(int d = 0; d < 4; d++){
                int i2 = i + di[d];
                int j2 = j + dj[d];
                if(i2 < 0 || i2 >= n || j2 < 0 || j2 >= m) continue;
                if(grid[i2][j2] == '#') continue;
                deg++;
            }
            if(deg > 2){
                vertId[i][j] = nextId++;
            }
        }
    }
    g.resize(nextId);
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if(vertId[i][j] == -1) continue;
            for(int d1 = 0; d1 < 4; d1++){
                int dist = 1;
                int pi = i, pj = j;
                int ci = i + di[d1];
                int cj = j + dj[d1];
                if(ci < 0 || ci >= n || cj < 0 || cj >= m) continue;
                if(grid[ci][cj] == '#') continue;
                while(vertId[ci][cj] == -1){
                    for(int d = 0; d < 4; d++){
                        int i2 = ci + di[d];
                        int j2 = cj + dj[d];
                        if(i2 < 0 || i2 >= n || j2 < 0 || j2 >= m) continue;
                        if(grid[i2][j2] == '#') continue;
                        if(i2 == pi && j2 == pj) continue;
                        dist++;
                        pi = ci, pj = cj;
                        ci = i2, cj = j2;
                        break;
                    }
                }
                g[vertId[i][j]].emplace_back(vertId[ci][cj], dist);
                g[vertId[ci][cj]].emplace_back(vertId[i][j], dist);
            }
        }
    }
    vis.assign(nextId, false);
    cout << calc(0) << "\n";
}