#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int)size(x)
constexpr int LOG = 18;

int sign(int x){
    if(x == 0) return 0;
    return x < 0 ? -1 : 1;
}

vector<vector<int>> g;
vector<vector<int>> jump;
vector<int> depth;
vector<vector<int>> childs;

int lift(int v, int x){
    for(int i = 0; i < LOG; i++){
        if(x & (1<<i)) v = jump[i][v];
    }
    return v;
}

int lca(int u, int v){
    if(depth[u] < depth[v]) swap(u, v);
    u = lift(u, depth[u] - depth[v]);
    if(u == v) return u;
    for(int i = LOG-1; i >= 0; i--){
        if(jump[i][u] != jump[i][v]){
            u = jump[i][u];
            v = jump[i][v];
        }
    }
    return jump[0][u];
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
                g[i].push_back(top[x][y]);
            }
            top[x][y] = i;
        });
        h[i] += z2 - z1 + 1;
        sort(g[i].begin(), g[i].end());
        g[i].resize(unique(g[i].begin(), g[i].end()) - g[i].begin());
    }
    // g is in reverse order!
    // 0, ..., n is topological order of g
    // build dominator tree of DAG in O(m log n)
    // by calculating lca of tree vertices having edge to v
    jump.assign(LOG, vector<int>(n+1));
    depth.resize(n+1);
    childs.resize(n+1);
    for(int v = 1; v <= n; v++){
        int dom = g[v][0];
        for(int u : g[v]){
            dom = lca(dom, u);
        }
        depth[v] = 1 + depth[dom];
        childs[dom].push_back(v);
        jump[0][v] = dom;
        for(int k = 1; k < LOG; k++){
            jump[k][v] = jump[k-1][jump[k-1][v]];
        }
    }
    int ans1 = 0, ans2 = 0;
    for(int v = 1; v <= n; v++){
        ans1 += childs[v].empty();
    }
    vector<int> subSize(n+1, 1);
    for(int v = n; v >= 1; v--){
        for(int u : childs[v]){
            subSize[v] += subSize[u];
        }
        ans2 += subSize[v]-1;
    }
    cout << ans1 << " " << ans2 << "\n";
}