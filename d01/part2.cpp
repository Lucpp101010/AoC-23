#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int)size(x)

vector<pair<string, int>> mp = {
    {"1", 1}, 
    {"2", 2},
    {"3", 3},
    {"4", 4},
    {"5", 5},
    {"6", 6},
    {"7", 7},
    {"8", 8},
    {"9", 9},
    {"one", 1},
    {"two", 2},
    {"three", 3},
    {"four", 4},
    {"five", 5},
    {"six", 6},
    {"seven", 7},
    {"eight", 8},
    {"nine", 9}
};

int main(){
    int ans = 0;
    string s;
    while(cin >> s){
        int last = -1;
        for(int i = 0; i < sz(s); i++){
            int x = -1;
            for(auto& [t, val] : mp){
                bool ok = true;
                for(int j = 0; j < sz(t) && ok; j++){
                    if(j+i == sz(s)) ok = false;
                    else if(t[j] != s[i+j]) ok = false;
                }
                if(ok) x = val;
            }
            if(x == -1) continue;
            ans += (last == -1 ? x : 0) * 10;
            last = x;
        }
        ans += last;
    }
    cout << ans << "\n";
}