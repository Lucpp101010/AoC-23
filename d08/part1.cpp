#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int)size(x)

int main(){
    string dir;
    cin >> dir;
    map<string, pair<string, string>> mp;
    string str;
    while(cin >> str){
        string from = str;
        cin >> str;
        cin >> str;
        string toL = str.substr(1, 3);
        string toR;
        cin >> toR;
        toR.pop_back();
        mp[from] = {toL, toR};
    }
    int ans = 0, i = 0;
    string cur = "AAA";
    while(cur != "ZZZ"){
        ans++;
        if(dir[i] == 'L') cur = mp[cur].first;
        else cur = mp[cur].second;
        i++;
        if(i == sz(dir)) i = 0;
    }
    cout << ans << "\n";
}