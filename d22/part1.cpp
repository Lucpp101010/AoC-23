#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int)size(x)

int sign(int x){
    if(x == 0) return 0;
    return x < 0 ? -1 : 1;
}

vector<vector<int>> g;
vector<bool> vis;

void dfs(int v){
    vis[v] = true;
    for(int u : g[v]){
        if(!vis[u]) dfs(u);
    }
}

int main(){
    string line;
    vector<tuple<int, int, int, int, int, int>> bricks;
    int m = 0;
    while(cin >> line){
        stringstream ss(line);
        int x1, y1, z1, x2, y2, z2;
        char sep;
        ss >> x1 >> sep >> y1 >> sep >> z1 >> sep 
           >> x2 >> sep >> y2 >> sep >> z2;
        if(z1 > z2) swap(z1, z2);
        bricks.emplace_back(z1, x1, y1, z2, x2, y2);
        m = max({m, x1, x2, y1, y2});
    }
    sort(bricks.begin(), bricks.end());
    int n = sz(bricks);
    g.resize(n+1);
    vector<int> h(n+1);
    vector<vector<int>> top(m+1, vector<int>(m+1, 0));
    for(int i = 1; i <= n; i++){
        auto [z1, x1, y1, z2, x2, y2] = bricks[i-1];
        auto forLine = [&](function<void(int, int)> f){
            int x = x1, y = y1;
            f(x, y);
            while(x != x2 || y != y2){
                x += sign(x2 - x);
                y += sign(y2 - y);
                f(x, y);
            }
        };
        forLine([&](int x, int y){
            h[i] = max(h[i], h[top[x][y]]);
        });
        forLine([&](int x, int y){
            if(h[top[x][y]] == h[i]){
                g[top[x][y]].push_back(i);
            }
            top[x][y] = i;
        });
        h[i] += z2 - z1 + 1;
    }
    for(int i = 0; i <= n; i++){
        sort(g[i].begin(), g[i].end());
        g[i].resize(unique(g[i].begin(), g[i].end()) - g[i].begin());
    }
    int ans = n;
    for(int v = 1; v <= n; v++){
        vis.assign(n+1, false);
        vis[v] = true;
        dfs(0);
        for(int u = 0; u <= n; u++){
            if(!vis[u]){
                ans--;
                break;
            }
        }
    }
    cout << ans << "\n";
}