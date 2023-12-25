#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int)size(x)


int n;
vector<vector<int>> g;

int main(){
    map<string, int> mp;
    auto getId = [&](string s){
        if(!mp.contains(s)){
            mp.emplace(s, sz(mp));
            g.push_back(vector<int>());
        }
        return mp[s];
    };
    string line;
    while(getline(cin, line)){
        stringstream ss(line);
        string from, to;
        ss >> from;
        from.pop_back();
        int v = getId(from);
        while(ss >> to){
            int u = getId(to);
            g[v].push_back(u);
            g[u].push_back(v);
        }
    }
    n = sz(g);
    // use stoer-wagner algo to find global min cut:
    vector<list<int>> comp(n);
    for(int i = 0; i < n; i++) comp[i].push_back(i);
    for(int it = 0; it < n-1; it++){
        int start = 0;
        while(comp[start].empty()) start++;
        priority_queue<pair<int, int>> pq;
        pq.emplace(0, start);
        vector<int> val(n);
        int cur = 0;
        vector<pair<int, int>> st;
        while(!pq.empty()){
            auto [x, v] = pq.top(); pq.pop();
            if(val[v] == -1) continue;
            val[v] = -1;
            for(int u : g[v]){
                if(comp[u].empty()) continue;
                if(val[u] >= 0){
                    val[u]++;
                    cur++;
                    pq.emplace(val[u], u);
                }
                else if(u != v) cur--;
            }
            st.emplace_back(cur, v);
        }
        int t = st.back().second;
        st.pop_back();
        int s = st.back().second;
        int cut = st.back().first;
        if(cut == 3){
            list<int> c1, c2;
            for(int v = 0; v < n; v++){
                if(v != t) c1.splice(c1.end(), comp[v]);
            }
            c2 = comp[t];
            // for(int v : c1) cerr << v << " ";
            // cerr << "\n";
            // for(int v : c2) cerr << v << " ";
            // cerr << "\n";
            cout << sz(c1) * sz(c2) << "\n";
            return 0;
        }
        g[s].insert(g[s].end(), g[t].begin(), g[t].end());
        g[t].clear();
        comp[s].splice(comp[s].end(), comp[t]);
        for(int v = 0; v < n; v++){
            for(int &u : g[v]){
                if(u == t) u = s;
            }
        }
    }
    cout << "No cut of size 3 found :(\n";
}