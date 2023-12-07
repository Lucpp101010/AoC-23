#include <bits/stdc++.h>
using namespace std;
using ll = long long;

map<char, int> val = {
    {'T', 0},
    {'J', 1},
    {'Q', 2},
    {'K', 3},
    {'A', 4}
};

int compChar(char a, char b){
    int va = a-'0', vb = b-'0';
    if(va > 9) va = 10 + val[a];
    if(vb > 9) vb = 10 + val[b];
    return va - vb;
}

vector<int> getCounts(string s){
    map<char, int> cnt;
    for(char c : s) cnt[c]++;
    vector<pair<int, char>> v;
    for(auto [c, i] : cnt) v.emplace_back(i, c);
    sort(v.rbegin(), v.rend());
    vector<int> w;
    for(auto [i, c] : v) w.push_back(i);
    return w;
}

int getHandVal(string s){
    vector<int> cnt = getCounts(s);
    if(cnt[0] == 5) return 6;
    if(cnt[0] == 4) return 5;
    if(cnt[0] == 3 && cnt[1] == 2) return 4;
    if(cnt[0] == 3) return 3;
    if(cnt[0] == 2 && cnt[1] == 2) return 2;
    if(cnt[0] == 2) return 1;
    return 0;
}

bool compHand(string a, string b){
    int va = getHandVal(a), vb = getHandVal(b);
    if(va < vb) return true;
    if(va > vb) return false;
    for(int i = 0; i < 5; i++){
        int co = compChar(a[i], b[i]);
        if(co < 0) return true;
        if(co > 0) return false;
    }
    return false;
}

int main(){
    string str;
    vector<string> hands;
    vector<ll> bids;
    while(cin >> str){
        hands.push_back(str);
        cin >> str;
        bids.push_back(stol(str));
    }
    int n = (int)hands.size();
    vector<int> ord(n);
    for(int i = 0; i < n; i++) ord[i] = i;
    sort(ord.begin(), ord.end(), [&](int i, int j){
        return compHand(hands[i], hands[j]);
    });
    ll ans = 0;
    for(int i = 0; i < n; i++){
        ans += (i+1) * bids[ord[i]];
    }
    cout << ans << "\n";
}