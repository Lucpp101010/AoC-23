#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int)size(x)
using ll = long long;

int main(){
    vector<vector<int>> g;
    vector<vector<int>> rev;
    vector<int> type; // 0 = flip-flop, 1 = conjunction, 2 = broadcast
    int start;
    map<string, int> mpId;
    auto getId = [&](string s){
        if(!mpId.contains(s)){
            mpId.emplace(s, sz(mpId));
            g.push_back(vector<int>());
            rev.push_back(vector<int>());
            type.push_back(0);
        }
        return mpId[s];
    };
    string line;
    while(getline(cin, line)){
        stringstream ss(line);
        string from, to;
        ss >> from >> to;
        int idFrom;
        if(from[0] == 'b'){
            idFrom = getId(from);
            start = idFrom;
            type[idFrom] = 2;
        }
        else{
            idFrom = getId(from.substr(1));
            if(from[0] == '%') type[idFrom] = 0;
            else type[idFrom] = 1;
        }
        while(ss >> to){
            if(to.back() == ',') to.pop_back();
            int idTo = getId(to);
            g[idFrom].push_back(idTo);
            rev[idTo].push_back(idFrom);
        }
    }
    vector<int> state(sz(g));
    vector<vector<int>> last(sz(g), vector<int>(sz(g)));
    ll cnt[2] = {0, 0};
    for(int it = 0; it < 1000; it++){
        queue<tuple<int, int, int>> q;
        q.emplace(start, -1, 0);
        while(!q.empty()){
            auto [u, from, p] = q.front(); q.pop();
            cnt[p]++;
            if(type[u] == 2){
                for(int v : g[u]){
                    q.emplace(v, u, p);
                }
            }
            else if(type[u] == 0){
                if(p == 0){
                    state[u] ^= 1;
                    for(int v : g[u]){
                        q.emplace(v, u, state[u]);
                    }
                }
            }
            else{
                last[u][from] = p;
                int send = 0;
                for(int v : rev[u]){
                    if(last[u][v] == 0) send = 1;
                }
                for(int v : g[u]){
                    q.emplace(v, u, send);
                }
            }
        }
    }
    ll ans = cnt[0] * cnt[1];
    cout << ans << "\n";
}