#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define sz(x) (int)size(x)

int main(){
    vector<string> v;
    string str;
    while(cin >> str) v.push_back(str);
    vector<string> v2;
    for(int i = 0; i < sz(v); i++){
        v2.push_back(v[i]);
        bool ok = true;
        for(char c : v[i]){
            if(c == '#') ok = false;
        }
        if(ok) v2.push_back(v[i]);
    }
    v = v2;
    v2.clear();
    v2.resize(sz(v));
    for(int j = 0; j < sz(v[0]); j++){
        bool ok = true;
        for(int i = 0; i < sz(v); i++){
            v2[i].push_back(v[i][j]);
            if(v[i][j] == '#') ok = false;
        }
        if(ok) for(int i = 0; i < sz(v); i++){
            v2[i].push_back(v[i][j]);
        }
    }
    v = v2;
    vector<pair<int, int>> pos;
    for(int i = 0; i < sz(v); i++){
        for(int j = 0; j < sz(v[0]); j++){
            if(v[i][j] == '#') pos.emplace_back(i, j);
        }
    }
    ll ans = 0;
    for(int i = 0; i < sz(pos); i++){
        for(int j = i+1; j < sz(pos); j++){
            ans += abs(pos[i].first - pos[j].first) + abs(pos[i].second - pos[j].second);
        }
    }
    cout << ans << "\n";
}