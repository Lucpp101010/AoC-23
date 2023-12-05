#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main(){
    string line, str;
    set<ll> v, v2;
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
            ll x;
            while(ss >> x) v.insert(x);
        }
        else if(headerMode){
            headerMode = false;
        }
        else{
            ll de, so, len;
            ss >> de >> so >> len;
            set<ll> v3;
            for(ll x : v){
                if(so <= x && x < so + len){
                    v2.insert(de + x - so);
                }
                else v3.insert(x);
            }
            v = v3;
        }
    }
    v.insert(v2.begin(), v2.end());
    cout << *v.begin() << "\n";
}