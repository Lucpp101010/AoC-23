#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll getScore(int cnt){
    return cnt == 0 ? 0 : 1ll << (cnt-1);
}

int main(){
    ll ans = 0;
    set<ll> s;
    int cnt = 0;
    bool sMode = true;
    string str;
    while(cin >> str){
        if(str == "Card"){
            ans += getScore(cnt);
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
    ans += getScore(cnt);
    cout << ans << "\n";
}