#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define sz(x) (int)size(x)

ll calc(vector<ll> v){
    if(v.empty()) return 0;
    int n = sz(v);
    vector<ll> w(n-1);
    for(int i = 0; i < n-1; i++){
        w[i] = v[i+1] - v[i];
    }
    return calc(w) + v.back();
}

int main(){
    string line;
    ll ans = 0;
    while(getline(cin, line)){
        vector<ll> v;
        stringstream ss(line);
        ll x;
        while(ss >> x) v.push_back(x);
        if(v.empty()) break;
        ans += calc(v);
    }
    cout << ans << "\n";
}