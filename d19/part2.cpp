#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define sz(x) (int)size(x)

vector<string> split(string s, char d){
    string cur;
    vector<string> v;
    for(char c : s){
        if(c == d){
            v.push_back(cur);
            cur = "";
        }
        else cur.push_back(c);
    }
    if(cur != "") v.push_back(cur);
    return v;
}

struct Rule{
    int ind = -1;
    ll val = 0;
    int type; // 0: <, 1: >, 2: true
    string next;
};

map<char, int> toInd = {
    {'x', 0},
    {'m', 1},
    {'a', 2},
    {'s', 3}
};

map<string, vector<Rule>> rules;

ll calc(string cur, vector<ll> mi, vector<ll> ma){
    if(cur == "R") return 0;
    ll ans = 0;
    if(cur == "A"){
        ans = 1;
        for(int i = 0; i < 4; i++){
            ll diff = ma[i] - mi[i];
            if(diff <= 0) diff = 0;
            ans *= diff;
        }
        return ans;
    }
    for(Rule r : rules[cur]){
        if(r.type == 2){
            ans += calc(r.next, mi, ma);
        }
        else{
            vector<ll> mi2 = mi, ma2 = ma;
            if(r.type == 0){
                ma2[r.ind] = min(ma2[r.ind], r.val);
                mi[r.ind] = max(mi[r.ind], r.val);
            }
            else{
                mi2[r.ind] = max(mi2[r.ind], r.val + 1);
                ma[r.ind] = min(ma[r.ind], r.val + 1);
            }
            ans += calc(r.next, mi2, ma2);
        }
    }
    return ans;
}

int main(){
    string line;
    bool readParts = false;
    while(getline(cin, line)){
        if(line.empty()) break;
        line.pop_back();
        if(!readParts){
            vector<string> v = split(line, '{');
            string name = v[0];
            v = split(v[1], ',');
            vector<Rule> myRules;
            for(string s : v){
                Rule r;
                vector<string> w = split(s, ':');
                if(sz(w) == 1){
                    r.type = 2;
                    r.next = w[0];
                }
                else{
                    r.ind = toInd[w[0][0]];
                    r.val = stoll(w[0].substr(2));
                    r.type = (w[0][1] == '<' ? 0 : 1);
                    r.next = w[1];
                }
                myRules.push_back(r);
            }
            rules[name] = myRules;
        }
    }
    // Probably there doesn't exist fast solution for general graphs (even DAGs)...
    // maybe input is tree:
    // set<string> hasIncoming;
    // for(auto [name, rule] : rules){
    //     for(Rule r : rule){
    //         if(r.next != "A" && r.next != "R"){
    //             if(hasIncoming.contains(r.next)){
    //                 cerr << "No tree :(\n";
    //                 return 0;
    //             }
    //             hasIncoming.insert(r.next);
    //         }
    //     }
    // }
    // Yes it is tree!
    ll ans = calc("in", vector<ll>(4, 1), vector<ll>(4, 4001));
    cout << ans << "\n";
}