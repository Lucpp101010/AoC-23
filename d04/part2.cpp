#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main(){
    ll ans = 0;
    set<ll> s;
    int cnt = 0;
    vector<int> v;
    bool sMode = true;
    string str;
    while(cin >> str){
        if(str == "Card"){
            v.push_back(cnt);
            cnt = 0;
            s.clear();
            sMode = true;
        }
        else if(str == "|"){
            sMode = false;
        }
        else if(str.back() != ':'){
            ll x = stoll(str);
            if(sMode) s.insert(x);
            else if(s.contains(x)) cnt++;
        }
    }
    v.erase(v.begin());
    v.push_back(cnt);
    int n = (int)v.size();
    vector<ll> dp(n, 1);
    for(int i = 0; i < n; i++){
        ans += dp[i];
        for(int j = 1; j <= v[i]; j++){
            if(i+j >= n) break;
            dp[i+j] += dp[i];
        }
    }
    cout << ans << "\n";
}