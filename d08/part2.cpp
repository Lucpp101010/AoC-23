#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int)size(x)
using ll = long long;

string dir;
map<string, pair<string, string>> mp;

pair<int, vector<int>> simu(string s){
    map<pair<string, int>, int> memo;
    vector<int> hist = {0};
    int dist = 0, i = 0;
    memo[{s, 0}] = 0;
    while(true){
        dist++;
        if(dir[i] == 'L') s = mp[s].first;
        else s = mp[s].second;
        i++;
        if(i == sz(dir)) i = 0;
        if(memo.contains({s, i})){
            return {memo[{s, i}], hist};
        }
        hist.push_back(s.back() == 'Z');
        memo[{s, i}] = dist;
    }
}

int main(){
    cin >> dir;
    string str;
    vector<string> start;
    while(cin >> str){
        string from = str;
        cin >> str;
        cin >> str;
        string toL = str.substr(1, 3);
        string toR;
        cin >> toR;
        toR.pop_back();
        mp[from] = {toL, toR};
        if(from.back() == 'A') start.push_back(from);
    }
    vector<pair<int, vector<int>>> v;
    for(string s : start){
        v.push_back(simu(s));
    }
    // Hope that each cycle contains at most one valid ending node
    // => use CRT
    vector<ll> b, m;
    for(auto [d, vec] : v){
        m.push_back(sz(vec) - d);
        int pos = -1;
        for(int i = 0; i < sz(vec); i++){
            if(vec[i] == 1){
                assert(pos == -1);
                pos = i;
            }
        }
        b.push_back(pos);
    }
    // Numbers might not be coprime, that sounds annoying.
    // So look at the numbers once again:
    for(int i = 0; i < sz(b); i++){
        cerr << b[i] << " " << m[i] << "\n";
    }
    // They are the same! So we can simply take lcm()
    ll ans = 1;
    for(ll x : b) ans = lcm(ans, x);
    cout << ans << "\n";
}