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
    while(cin >> line) grid.push_back(line);
    int n = sz(grid), m = sz(grid[0]);
    int ans = 0;
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
                int len = 1;
                while(grid[x][y] != 'S'){
                    len++;
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
                ans = len / 2;
            }
        }
    }
    cout << ans << "\n";
}