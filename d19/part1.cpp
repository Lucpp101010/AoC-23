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

bool check(vector<ll> item, Rule rule){
    if(rule.type == 2) return true;
    else if(rule.type == 0) return item[rule.ind] < rule.val;
    else return item[rule.ind] > rule.val; 
}

int main(){
    string line;
    bool readParts = false;
    map<string, vector<Rule>> rules;
    vector<vector<ll>> items;
    while(getline(cin, line)){
        if(line.empty()){
            if(readParts) break;
            readParts = true;
            continue;
        }
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
        else{
            line = line.substr(1);
            vector<string> v = split(line, ',');
            vector<ll> item;
            for(string s : v){
                item.push_back(stoll(s.substr(2)));
            }
            items.push_back(item);
        }
    }
    ll ans = 0;
    for(vector<ll> item : items){
        string cur = "in";
        while(cur != "A" && cur != "R"){
            for(Rule r : rules[cur]){
                if(check(item, r)){
                    cur = r.next;
                    break;
                }
            }
        }
        if(cur == "A"){
            for(ll x : item) ans += x;
        }
    }
    cout << ans << "\n";
}