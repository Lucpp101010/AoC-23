#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main(){
    string s;
    ll ans = 0;
    while(getline(cin, s)){
        stringstream ss(s);
        string useless;
        ss >> useless >> useless;
        int r = 0, g = 0, b = 0;
        while(true){
            int cnt; string col;
            ss >> cnt >> col;
            if(col[0] == 'r') r = max(r, cnt);
            if(col[0] == 'g') g = max(g, cnt);
            if(col[0] == 'b') b = max(b, cnt);
            if(col.back() != ',' && col.back() != ';') break;
        }
        ans += (ll)r*g*b;
    }
    cout << ans << "\n";
}