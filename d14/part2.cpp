#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int)size(x)
using ll = long long;

int n, m;

vector<string> tiltN(vector<string> grid){
    for(int j = 0; j < m; j++){
        int cnt = 0;
        for(int i = n-1; i >= 0; i--){
            if(grid[i][j] == 'O'){
                cnt++;
                grid[i][j] = '.';
            }
            if(grid[i][j] == '#'){
                for(int k = 1; k <= cnt; k++){
                    grid[i+k][j] = 'O';
                }
                cnt = 0;
            }
        }
        for(int k = 0; k < cnt; k++){
            grid[k][j] = 'O';
        }
    }
    return grid;
}

vector<string> tiltW(vector<string> grid){
    for(int i = 0; i < n; i++){
        int cnt = 0;
        for(int j = m-1; j >= 0; j--){
            if(grid[i][j] == 'O'){
                cnt++;
                grid[i][j] = '.';
            }
            if(grid[i][j] == '#'){
                for(int k = 1; k <= cnt; k++){
                    grid[i][j+k] = 'O';
                }
                cnt = 0;
            }
        }
        for(int k = 0; k < cnt; k++){
            grid[i][k] = 'O';
        }
    }
    return grid;
}

vector<string> tiltS(vector<string> grid){
    for(int j = 0; j < m; j++){
        int cnt = 0;
        for(int i = 0; i < n; i++){
            if(grid[i][j] == 'O'){
                cnt++;
                grid[i][j] = '.';
            }
            if(grid[i][j] == '#'){
                for(int k = 1; k <= cnt; k++){
                    grid[i-k][j] = 'O';
                }
                cnt = 0;
            }
        }
        for(int k = 1; k <= cnt; k++){
            grid[n-k][j] = 'O';
        }
    }
    return grid;
}

vector<string> tiltE(vector<string> grid){
    for(int i = 0; i < n; i++){
        int cnt = 0;
        for(int j = 0; j < m; j++){
            if(grid[i][j] == 'O'){
                cnt++;
                grid[i][j] = '.';
            }
            if(grid[i][j] == '#'){
                for(int k = 1; k <= cnt; k++){
                    grid[i][j-k] = 'O';
                }
                cnt = 0;
            }
        }
        for(int k = 1; k <= cnt; k++){
            grid[i][m-k] = 'O';
        }
    }
    return grid;
}

vector<string> tiltCycle(vector<string> grid){
    return tiltE(tiltS(tiltW(tiltN(grid))));
}

int main(){
    vector<string> grid;
    string line;
    while(cin >> line) grid.push_back(line);
    n = sz(grid), m = sz(grid[0]);
    map<vector<string>, int> dist;
    vector<vector<string>> states;
    dist[grid] = 0;
    states.push_back(grid);
    int curDist = 0;
    int steps = 1e9;
    while(true){
        grid = tiltCycle(grid);
        curDist++;
        if(!dist.contains(grid)){
            states.push_back(grid);
            dist[grid] = curDist;
        }
        else{
            int oldDist = dist[grid];
            steps -= oldDist;
            steps %= curDist - oldDist;
            steps += oldDist;
            grid = states[steps];
            ll ans = 0;
            for(int i = 0; i < n; i++){
                for(int j = 0; j < m; j++){
                    if(grid[i][j] == 'O') ans += n-i;
                }
            }
            cout << ans << "\n";
            break;
        }
    }
    // for(string s : grid) cerr << s << "\n";
}