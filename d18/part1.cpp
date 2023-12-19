#include <bits/stdc++.h>
using namespace std;

vector<int> dx = {1, -1, 0, 0};
vector<int> dy = {0, 0, 1, -1};


int sign(int x){
    if(x == 0) return 0;
    return x > 0 ? 1 : -1;
}

int main(){
    string line;
    vector<tuple<char, int>> plan;
    int maxSize = 1;
    while(getline(cin, line)){
        if(line.empty()) break;
        stringstream ss(line);
        char dir;
        int len;
        ss >> dir >> len;
        plan.emplace_back(dir, len);
        maxSize += len;
    }
    maxSize *= 2;
    vector<vector<int>> vis(maxSize, vector<int>(maxSize));
    {
        int x = maxSize/2, y = maxSize/2;
        for(auto [dir, len] : plan){
            int x2 = x, y2 = y;
            if(dir == 'U') x2 += len;
            if(dir == 'D') x2 -= len;
            if(dir == 'L') y2 -= len;
            if(dir == 'R') y2 += len;
            while(x != x2 || y != y2){
                vis[x][y] = 1;
                x += sign(x2 - x);
                y += sign(y2 - y);
            }
            vis[x][y] = 1;
        }
    }
    stack<pair<int, int>> st;
    st.emplace(0, 0);
    vis[0][0] = 2;
    while(!st.empty()){
        auto [x, y] = st.top();
        st.pop();
        for(int i = 0; i < 4; i++){
            int x2 = x + dx[i];
            int y2 = y + dy[i];
            if(x2 < 0 || x2 >= maxSize || y2 < 0 || y2 >= maxSize) continue;
            if(vis[x2][y2] == 0){
                vis[x2][y2] = 2;
                st.emplace(x2, y2);
            }
        }
    }
    int ans = 0;
    for(int i = 0; i < maxSize; i++){
        for(int j = 0; j < maxSize; j++){
            ans += vis[i][j] < 2;
        }
    }
    cout << ans << "\n";
}