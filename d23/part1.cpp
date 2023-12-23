#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int)size(x)

constexpr int inf = 1e8;

vector<int> di = {-1, 0, 1, 0};
vector<int> dj = {0, 1, 0, -1};

int n, m;
vector<string> grid;
vector<vector<vector<int>>> dp;

int calc(int i, int j, int pd){
    if(dp[i][j][pd] != -1) return dp[i][j][pd];
    int res = -inf;
    for(int d = 0; d < 4; d++){
        if(d == (pd + 2) % 4) continue;
        if(grid[i][j] == '^' && d != 0) continue;
        if(grid[i][j] == '>' && d != 1) continue;
        if(grid[i][j] == 'v' && d != 2) continue;
        if(grid[i][j] == '<' && d != 3) continue;
        int i2 = i + di[d];
        int j2 = j + dj[d];
        if(i2 < 0 || i2 >= n || j2 < 0 || j2 >= m) continue;
        if(grid[i2][j2] == '#') continue;
        res = max(res, calc(i2, j2, d) + 1);
    }
    return dp[i][j][pd] = res;
}

int main(){
    string line;
    while(cin >> line) grid.push_back(line);
    n = sz(grid), m = sz(grid[0]);
    dp.assign(n, vector<vector<int>>(n, vector<int>(4, -1)));
    dp[n-1][m-2][2] = 0;
    cout << calc(0, 1, 2) << "\n";
}