#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int)size(x)
using ll = long long;

int main(){
    vector<string> strings;
    vector<vector<int>> blocks;
    string str;
    while(cin >> str){
        strings.push_back(str);
        vector<int> v;
        cin >> str;
        int x;
        char comma;
        stringstream ss(str);
        ss >> x;
        v.push_back(x);
        while(ss >> comma >> x) v.push_back(x);
        blocks.push_back(v);
    }
    ll ans = 0;
    for(int tc = 0; tc < sz(strings); tc++){
        string s = strings[tc];
        vector<int> v = blocks[tc];
        int n = sz(s), m = sz(v);
        vector<vector<ll>> dp(n+1, vector<ll>(m+1));
        dp[0][0] = 1;
        for(int i = 1; i <= n; i++){
            for(int j = 0; j <= m; j++){
                if(s[i-1] == '.') dp[i][j] += dp[i-1][j];
                else{
                    if(j > 0){
                        bool ok = true;
                        int len = v[j-1];
                        for(int k = 1; k <= len; k++){
                            if(k > i){
                                ok = false;
                                break;
                            }
                            if(s[i-k] == '.') ok = false;
                        }
                        if(len+1 <= i && s[i-len-1] == '#') ok = false;
                        if(ok) dp[i][j] += dp[max(0, i-len-1)][j-1];
                    }
                    if(s[i-1] == '?') dp[i][j] += dp[i-1][j];
                }
            }
        }
        ans += dp[n][m];
    }
    cout << ans << "\n";
}