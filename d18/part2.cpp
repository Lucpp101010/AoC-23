#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main(){
    string line;
    vector<tuple<char, ll>> plan;
    while(getline(cin, line)){
        if(line.empty()) break;
        stringstream ss(line);
        char dir;
        ll len;
        string color;
        ss >> dir >> len >> color;
        // color.pop_back();
        // dir = "RDLU"[color.back() - '0'];
        // color.pop_back();
        // color = color.substr(2);
        // ss = stringstream(color);
        // ss >> hex >> len;
        plan.emplace_back(dir, len);
    }
    ll y = 0, ans = 1;
    for(auto [dir, len] : plan){
        if(dir == 'R'){
            ans += len * y;
        }
        if(dir == 'L'){
            ans -= len * (y-1);
        }
        if(dir == 'U'){
            y += len;
            ans += len;
        }
        if(dir == 'D'){
            y -= len;
        }
    }
    cout << ans << "\n";
}