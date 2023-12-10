#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int)size(x)

map<char, int> getMsk = {
    {'|', 0b1010},
    {'-', 0b0101},
    {'L', 0b1100},
    {'J', 0b1001},
    {'7', 0b0011},
    {'F', 0b0110},
    {'.', 0b0000}
};

vector<int> dx = {0, 1, 0, -1};
vector<int> dy = {-1, 0, 1, 0};

int main(){
    vector<string> grid;
    string line;
    while(cin >> line) grid.push_back("." + line + ".");
    int n = sz(grid), m = sz(grid[0]);
    grid.insert(grid.begin(), string(m, '.'));
    grid.push_back(string(m, '.'));
    n += 2;
    vector<vector<bool>> mark(2*n, vector<bool>(2*m));
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if(grid[i][j] == 'S'){
                int lx = i, ly = j, x, y;
                for(int d = 0; d < 4; d++){
                    x = lx + dx[d];
                    y = ly + dy[d];
                    if(x < 0 || x >= n || y < 0 || y >= m) continue;
                    if(getMsk[grid[x][y]] & (1 << (d^2))) break;
                }
                while(true){
                    mark[lx+x][ly+y] = true;
                    mark[2*x][2*y] = true;
                    if(grid[x][y] == 'S') break;
                    for(int d = 0; d < 4; d++){
                        if(getMsk[grid[x][y]] & (1 << d)){
                            int x2 = x + dx[d];
                            int y2 = y + dy[d];
                            if(x2 == lx && y2 == ly) continue;
                            lx = x, ly = y;
                            x = x2, y = y2;
                            break;
                        }
                    }
                }
            }
        }
    }
    queue<pair<int, int>> q;
    q.emplace(0, 0);
    while(!q.empty()){
        auto [x, y] = q.front();
        q.pop();
        for(int d = 0; d < 4; d++){
            int x2 = x + dx[d];
            int y2 = y + dy[d];
            if(x2 < 0 || x2 >= 2*n || y2 < 0 || y2 >= 2*m) continue;
            if(!mark[x2][y2]){
                mark[x2][y2] = true;
                q.emplace(x2, y2);
            }
        }
    }
    int ans = 0;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if(!mark[2*i][2*j]) ans++;
        }
    }
    cout << ans << "\n";
}