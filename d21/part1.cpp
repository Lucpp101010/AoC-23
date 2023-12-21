#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int)size(x)

vector<int> di = {1, -1, 0, 0};
vector<int> dj = {0, 0, 1, -1};

int main(){
    vector<string> grid;
    string line;
    while(cin >> line) grid.push_back(line);
    int n = sz(grid), m = sz(grid[0]);
    vector<pair<int, int>> cur;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if(grid[i][j] == 'S'){
                cur.emplace_back(i, j);
            }
        }
    }
    for(int step = 0; step < 64; step++){
        vector<vector<bool>> vis(n, vector<bool>(m));
        vector<pair<int, int>> nxt;
        for(auto [i, j] : cur){
            for(int d = 0; d < 4; d++){
                int i2 = i + di[d];
                int j2 = j + dj[d];
                if(i2 < 0 || i2 >= n || j2 < 0 || j2 >= m) continue;
                if(grid[i2][j2] == '#') continue;
                if(vis[i2][j2]) continue;
                nxt.emplace_back(i2, j2);
                vis[i2][j2] = true;
            }
        }
        cur = nxt;
    }
    cout << sz(cur) << "\n";
}