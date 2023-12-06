#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main(){
    string l1, l2;
    getline(cin, l1);
    getline(cin, l2);
    string str;
    stringstream ss1(l1), ss2(l2);
    ss1 >> str;
    ss2 >> str;
    vector<ll> t, d;
    ll x;
    while(ss1 >> x) t.push_back(x);
    while(ss2 >> x) d.push_back(x);
    int n = (int)t.size();
    ll ans = 1;
    for(int i = 0; i < n; i++){
        ll cnt = 0;
        for(ll y = 0; y <= t[i]; y++){
            cnt += (y * (t[i] - y) > d[i]);
        }
        ans *= cnt;
    }
    cout << ans << "\n";
}