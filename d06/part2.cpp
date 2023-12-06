#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll toNum(string s){
    ll res = 0;
    for(char c : s){
        int d = c-'0';
        if(0 <= d && d <= 9) res = 10*res + d;
    }
    return res;
}

int main(){
    string l1, l2;
    getline(cin, l1);
    getline(cin, l2);
    ll t = toNum(l1);
    ll d = toNum(l2);
    ll lo = 0, hi = t/2;
    while(lo+1 < hi){
        ll m = (lo + hi) / 2;
        if(m * (t - m) > d) hi = m;
        else lo = m;
    }
    ll mi = hi;
    ll ma = t-hi;
    ll ans = ma - mi + 1;
    cout << ans << "\n";
}