#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define sz(x) (int)size(x)

constexpr ll expand = 999'999;

int main(){
    vector<string> v;
    string str;
    while(cin >> str) v.push_back(str);
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
    int cnt = 0;
    for(int i = 0; i < sz(v); i++){
        bool ok = true;
        for(int j = 0; j < sz(v[0]); j++){
            if(v[i][j] == '#') ok = false, cnt++;
        }
        if(ok) ans += expand * cnt * (sz(pos) - cnt);
    }
    cnt = 0;
    for(int j = 0; j < sz(v[0]); j++){
        bool ok = true;
        for(int i = 0; i < sz(v); i++){
            if(v[i][j] == '#') ok = false, cnt++;
        }
        if(ok) ans += expand * cnt * (sz(pos) - cnt);
    }
    cout << ans << "\n";
}