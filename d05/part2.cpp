#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;

int main(){
    string line, str;
    set<pll> v, v2;
    bool headerMode = false;
    while(getline(cin, line)){
        if(line.empty()){
            v.insert(v2.begin(), v2.end());
            v2.clear();
            headerMode = true;
            continue;
        }
        stringstream ss(line);
        if(v.empty()){
            ss >> str;
            ll x, y;
            while(ss >> x) ss >> y, v.emplace(x, x+y-1);
        }
        else if(headerMode){
            headerMode = false;
        }
        else{
            ll de, so, len;
            ss >> de >> so >> len;
            set<pll> v3;
            for(auto [l, r] : v){
                if(r < so || l >= so + len){
                    v3.emplace(l, r);
                    continue;
                }
                if(l < so){
                    v3.emplace(l, so);
                    l = so;
                }
                if(r >= so + len){
                    v3.emplace(so + len, r);
                    r = so + len - 1;
                }
                v2.emplace(de + l - so, de + r - so);
            }
            v = v3;
        }
    }
    v.insert(v2.begin(), v2.end());
    cout << v.begin()->first << "\n";
}