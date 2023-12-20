#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int)size(x)
using ll = long long;

struct State{
    vector<int> flip;
    vector<vector<int>> last;
    bool operator < (const State &state) const{
        if(flip < state.flip) return true;
        if(flip > state.flip) return false;
        return last < state.last;
    }
};
int start, goal, beforeGoal;
vector<int> type; // 0 = flip-flop, 1 = conjunction, 2 = broadcast
vector<vector<int>> g;
vector<vector<int>> rev;

void simulate(State &state, const vector<bool>& verts){
    queue<tuple<int, int, int>> q;
    q.emplace(start, -1, 0);
    while(!q.empty()){
        auto [u, from, p] = q.front(); q.pop();
        if(!verts[u]) continue;
        if(type[u] == 2){
            for(int v : g[u]){
                q.emplace(v, u, p);
            }
        }
        else if(type[u] == 0){
            if(p == 0){
                state.flip[u] ^= 1;
                for(int v : g[u]){
                    q.emplace(v, u, state.flip[u]);
                }
            }
        }
        else{
            state.last[u][from] = p;
            int send = 0;
            for(int v : rev[u]){
                if(state.last[u][v] == 0) send = 1;
            }
            for(int v : g[u]){
                q.emplace(v, u, send);
            }
        }
    }
}

int main(){
    map<string, int> mpId;
    auto getId = [&](string s){
        if(!mpId.contains(s)){
            mpId.emplace(s, sz(mpId));
            g.push_back(vector<int>());
            rev.push_back(vector<int>());
            type.push_back(0);
            if(s == "rx") goal = mpId[s];
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
    // visualize graph with https://csacademy.com/app/graph_editor/
    // for(int i = 0; i < sz(g); i++) cout << i << "\n";
    // for(int u = 0; u < sz(g); u++){
    //     for(int v : g[u]){
    //         cout << u << " " << v << "\n";
    //     }
    // }
    // => 4 separate components!
    vector<vector<bool>> comps;
    vector<bool> vis(sz(g));
    for(int u = 0; u < sz(g); u++){
        if(u == goal) vis[u] = true;
        for(int v : g[u]){
            if(v == goal) vis[u] = true, beforeGoal = u;
        }
    }
    for(int s : g[start]){
        if(vis[s]) continue;
        stack<int> st;
        st.push(s);
        vis[s] = true;
        comps.push_back(vector<bool>(sz(g)));
        while(!st.empty()){
            int u = st.top(); st.pop();
            comps.back()[u] = true;
            for(int v : g[u]){
                if(!vis[v]){
                    vis[v] = true;
                    st.push(v);
                }
            }
        }
        comps.back()[start] = true;
    }
    ll ans = 1;
    for(int co = 0; co < sz(comps); co++){
        State state;
        state.flip.resize(sz(g));
        state.last.resize(sz(g), vector<int>(sz(g)));
        vector<int> bgi;
        map<State, int> memo;
        memo[state] = 0;
        int dist = 0;
        bgi.push_back(-1);
        while(true){
            simulate(state, comps[co]);
            dist++;
            if(memo.contains(state)){
                // 1 ...
                cerr << memo[state] << " " << dist << "\n";
                break;
            }
            memo[state] = dist;
        }
        // high is only written to beforeGoal on last step -> lcm
        ans = lcm(ans, dist-1);
    }
    cout << ans << "\n";
}