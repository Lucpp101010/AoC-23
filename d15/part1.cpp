#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main(){
    string s;
    cin >> s;
    ll ans = 0, cur = 0;
    for(char c : s){
        if(c == ',') ans += cur, cur = 0;
        else cur = (17 * (cur + (ll)c)) % 256;
    }
    ans += cur;
    cout << ans << "\n";
}