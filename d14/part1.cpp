#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int)size(x)
using ll = long long;

int main(){
    vector<string> grid;
    string line;
    while(cin >> line) grid.push_back(line);
    int n = sz(grid), m = sz(grid[0]);
    ll ans = 0;
    for(int j = 0; j < m; j++){
        int cnt = 0;
        for(int i = n-1; i >= 0; i--){
            if(grid[i][j] == 'O') cnt++;
            if(grid[i][j] == '#'){
                ans += cnt * (n-(i+1) + n-(i+1+cnt-1)) / 2;
                cnt = 0;
            }
        }
        ans += cnt * (n + n-(cnt-1)) / 2;
    }
    cout << ans << "\n";
}