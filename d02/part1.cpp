#include <bits/stdc++.h>
using namespace std;

int main(){
    string s;
    int i = 1, ans = 0;
    while(getline(cin, s)){
        stringstream ss(s);
        string useless;
        ss >> useless >> useless;
        bool ok = true;
        while(true){
            int cnt; string col;
            ss >> cnt >> col;
            if(col[0] == 'r' && cnt > 12) ok = false;
            if(col[0] == 'g' && cnt > 13) ok = false;
            if(col[0] == 'b' && cnt > 14) ok = false;
            if(col.back() != ',' && col.back() != ';') break;
        }
        if(ok) ans += i;
        i++;
    }
    cout << ans << "\n";
}