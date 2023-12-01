#include <bits/stdc++.h>
using namespace std;

int main(){
    int ans = 0;
    string s;
    while(cin >> s){
        int last = -1;
        for(char c : s){
            int x = c-'0';
            if(x < 0 || x > 9) continue;
            ans += (last == -1 ? x : 0) * 10;
            last = x;
        }
        ans += last;
    }
    cout << ans << "\n";
}