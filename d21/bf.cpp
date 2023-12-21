#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int)size(x)

vector<int> di = {1, -1, 0, 0};
vector<int> dj = {0, 0, 1, -1};

int main(){
    vector<string> grid;
    string line;
    while(cin >> line) grid.push_back(line);
    int n = sz(grid);
    set<pair<int, int>> cur;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(grid[i][j] == 'S'){
                cur.emplace(i, j);
            }
        }
    }
    for(int step = 0; step < 327; step++){
        set<pair<int, int>> nxt;
        for(auto [i, j] : cur){
            for(int d = 0; d < 4; d++){
                int i2 = i + di[d];
                int j2 = j + dj[d];
                // if(i2 < 0 || i2 >= n || j2 < 0 || j2 >= n) continue;
                if(grid[(i2%n+n)%n][(j2%n+n)%n] == '#') continue;
                nxt.emplace(i2, j2);
            }
        }
        cur = nxt;
    }
    cout << sz(cur) << "\n";
}