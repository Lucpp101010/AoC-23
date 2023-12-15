#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int)size(x)
using ll = long long;

int main(){
    string input;
    cin >> input;
    vector<string> cmds;
    cmds.push_back("");
    for(char c : input){
        if(c == ',') cmds.push_back("");
        else cmds.back().push_back(c);
    }
    vector<vector<pair<string, int>>> box(256);
    for(string cmd : cmds){
        string label;
        int hash = 0;
        for(char c : cmd){
            if(c =='=' || c == '-') break;
            label += c;
            hash = (17 * (hash + (int)c)) % 256;
        }
        if(cmd.back() == '-'){
            for(int i = 0; i < sz(box[hash]); i++){
                if(box[hash][i].first == label){
                    box[hash].erase(box[hash].begin() + i);
                    break;
                }
            }
        }
        else{
            int val = (int)(cmd.back() - '0');
            bool found = false;
            for(int i = 0; i < sz(box[hash]); i++){
                if(box[hash][i].first == label){
                    box[hash][i].second = val;
                    found = true;
                    break;
                }
            }
            if(!found){
                box[hash].emplace_back(label, val);
            }
        }
    }
    ll ans = 0;
    for(int i = 0; i < 256; i++){
        for(int j = 0; j < sz(box[i]); j++){
            ans += (i+1)*(j+1)*box[i][j].second;
        }
    }
    cout << ans << "\n";
}