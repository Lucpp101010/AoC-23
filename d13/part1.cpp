#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int)size(x)
using ll = long long;

int main(){
    cin.tie(0)->sync_with_stdio(false);
    string line;
    vector<string> curBlock;
    vector<vector<string>> blocks;
    while(getline(cin, line)){
        if(line.empty()){
            blocks.push_back(curBlock);
            curBlock.clear();
        }
        else curBlock.push_back(line);
    }
    if(!curBlock.empty()) blocks.push_back(curBlock);

    ll ans = 0;
    for(auto v : blocks){
        int n = sz(v), m = sz(v[0]);
        for(int i = 0; i < n-1; i++){
            bool ok = true;
            for(int j = 0; j < m; j++){
                for(int k = 0; k < n; k++){
                    if(i-k < 0 || i+k+1 >= n) break;
                    if(v[i-k][j] != v[i+k+1][j]) ok = false;
                }
            }
            if(ok) ans += 100 * (i+1);
        }
        for(int j = 0; j < m-1; j++){
            bool ok = true;
            for(int i = 0; i < n; i++){
                for(int k = 0; k < m; k++){
                    if(j-k < 0 || j+k+1 >= m) break;
                    if(v[i][j-k] != v[i][j+k+1]) ok = false;
                }
            }
            if(ok) ans += j+1;
        }
    }
    cout << ans << "\n";
}