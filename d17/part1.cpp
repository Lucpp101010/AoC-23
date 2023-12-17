#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int)size(x)

vector<int> di = {0, 1, 0, -1};
vector<int> dj = {1, 0, -1, 0};

constexpr int SIZE = 200;
constexpr int inf = 1e8;

int dist[SIZE][SIZE][4][3];

int main(){
    vector<vector<int>> grid;
    int n, m;
    {
        string str;
        vector<string> strings;
        while(cin >> str) strings.push_back(str);
        n = sz(strings), m = sz(strings[0]);
        grid.resize(n, vector<int>(m));
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                grid[i][j] = (int)(strings[i][j] - '0');
            }
        }
    }
    fill_n((int*)dist, sizeof(dist) / sizeof(int), inf);
    priority_queue<tuple<int, int, int, int, int>> pq;
    dist[0][1][0][0] = grid[0][1];
    dist[1][0][1][0] = grid[1][0];
    pq.emplace(-grid[0][1], 0, 1, 0, 0);
    pq.emplace(-grid[1][0], 1, 0, 1, 0);
    while(!pq.empty()){
        auto [d, i, j, dir, same] = pq.top();
        pq.pop();
        d = -d;
        if(d > dist[i][j][dir][same]) continue;
        for(int turn = -1; turn <= 1; turn++){
            int dir2 = (dir + turn + 4) % 4;
            int i2 = i + di[dir2];
            int j2 = j + dj[dir2];
            int same2 = (turn == 0 ? same+1 : 0);
            if(i2 < 0 || i2 >= n || j2 < 0 || j2 >= m || same2 >= 3) continue;
            int d2 = d + grid[i2][j2];
            if(d2 < dist[i2][j2][dir2][same2]){
                dist[i2][j2][dir2][same2] = d2;
                pq.emplace(-d2, i2, j2, dir2, same2);
            }
        }
    }
    int ans = inf;
    for(int dir = 0; dir < 4; dir++){
        for(int same = 0; same < 3; same++){
            ans = min(ans, dist[n-1][m-1][dir][same]);
        }
    }
    cout << ans << "\n";
}