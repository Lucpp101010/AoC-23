#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int)size(x)
using ll = long long;

vector<int> di = {1, -1, 0, 0};
vector<int> dj = {0, 0, 1, -1};

vector<string> grid;
int n;

vector<vector<int>> bfs(int si, int sj){
    queue<pair<int, int>> q;
    q.emplace(si, sj);
    vector<vector<int>> dist(n, vector<int>(n, -1));
    dist[si][sj] = 0;
    while(!q.empty()){
        auto [i, j] = q.front(); q.pop();
        for(int d = 0; d < 4; d++){
            int i2 = i + di[d];
            int j2 = j + dj[d];
            if(i2 < 0 || i2 >= n || j2 < 0 || j2 >= n) continue;
            if(grid[i2][j2] == '#') continue;
            if(dist[i2][j2] != -1) continue;
            dist[i2][j2] = dist[i][j] + 1;
            q.emplace(i2, j2);
        }
    }
    return dist;
}

int main(){
    string line;
    while(cin >> line) grid.push_back(line);
    n = sz(grid); // grid is n x n
    ll colorCnt[2] = {0, 0};
    {
        auto dist = bfs(n/2, n/2);
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                if(dist[i][j] != -1) colorCnt[dist[i][j]%2]++;
            }
        }
    }
    constexpr ll steps = 26501365;
    ll fullDist = steps / n;
    ll ans = colorCnt[1];
    for(int i = 1; i < fullDist; i++){
        ans += 4 * i * colorCnt[(i+1)&1];
    }
    for(int si = 0; si < n; si += n/2){
        for(int sj = 0; sj < n; sj += n/2){
            if(si == n/2 && sj == n/2) continue;
            bool corner = (si != n/2 && sj != n/2);
            ll remDist = steps - (corner ? 1 : n/2+1) - (fullDist-1)*n;
            auto dist = bfs(si, sj);
            for(int it = 0; remDist >= 0; it++, remDist -= n){
                for(int i = 0; i < n; i++){
                    for(int j = 0; j < n; j++){
                        if(dist[i][j] == -1) continue;
                        if(dist[i][j] % 2 == remDist % 2 && dist[i][j] <= remDist){
                            ans += (corner ? fullDist-1+it : 1);
                        }
                    }
                }
            }
        }
    }
    cout << ans << "\n";
}