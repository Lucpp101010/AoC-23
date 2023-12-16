#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int)size(x)

vector<int> di = {0, 1, 0, -1};
vector<int> dj = {1, 0, -1, 0};

map<char, vector<vector<int>>> moveTable = {
    {'.', {{0}, {1}, {2}, {3}}},
    {'/', {{3}, {2}, {1}, {0}}},
    {'\\', {{1}, {0}, {3}, {2}}},
    {'-', {{0}, {0, 2}, {2}, {0, 2}}},
    {'|', {{1, 3}, {1}, {1, 3}, {3}}}
};

int main(){
    vector<string> grid;
    string line;
    while(cin >> line) grid.push_back(line);
    int n = sz(grid), m = sz(grid[0]);
    vector<vector<vector<bool>>> vis(n, vector<vector<bool>>(m, vector<bool>(4)));
    stack<tuple<int, int, int>> st;
    st.emplace(0, 0, 0);
    vis[0][0][0] = true;
    while(!st.empty()){
        auto [i, j, dir] = st.top();
        st.pop();
        for(int dir2 : moveTable[grid[i][j]][dir]){
            int i2 = i + di[dir2];
            int j2 = j + dj[dir2];
            if(i2 < 0 || i2 >= n || j2 < 0 || j2 >= m) continue;
            if(vis[i2][j2][dir2]) continue;
            vis[i2][j2][dir2] = true;
            st.emplace(i2, j2, dir2);
        }
    }
    int ans = 0;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            bool ok = false;
            for(int d = 0; d < 4; d++) ok |= vis[i][j][d];
            ans += ok;
        }
    }
    cout << ans << "\n";
}