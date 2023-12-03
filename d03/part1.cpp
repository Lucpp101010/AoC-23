#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int)size(x)
using ll = long long;

vector<int> dx = {1, -1, 0, 0, 1, 1, -1, -1};
vector<int> dy = {0, 0, 1, -1, 1, -1, 1, -1};

bool isDigit(char c){
    return '0' <= c && c <= '9';
}

int main(){
    vector<string> v;
    {
        string line;
        while(getline(cin, line)){
            line.push_back('.');
            v.push_back(line);
        }
    }
    int n = sz(v), m = sz(v[0]);
    vector<vector<bool>> adj(n, vector<bool>(m));
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if(v[i][j] == '.' || isDigit(v[i][j])) continue;
            for(int d = 0; d < 8; d++){
                int i2 = i + dx[d], j2 = j + dy[d];
                if(i2 < 0 || i2 >= n || j2 < 0 || j2 >= m) continue;
                adj[i2][j2] = true;
            }
        }
    }
    ll ans = 0;
    for(int i = 0; i < n; i++){
        int cur = 0;
        bool ok = false;
        for(int j = 0; j < m; j++){
            if(!isDigit(v[i][j])){
                if(ok) ans += cur;
                cur = 0;
                ok = false;
            }
            else{
                if(adj[i][j]) ok = true;
                cur = 10 * cur + (int)(v[i][j] - '0');
            }
        }
    }
    cout << ans << "\n";
}