#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using lll = __int128_t;
#define sz(x) (int)size(x)

constexpr ll low = 200000000000000, high = 400000000000000;

template<typename T>
T sign(T x){
    if(x == 0) return 0;
    return x < 0 ? -1 : 1;
}

int main(){
    vector<ll> x, y, z, vx, vy, vz;
    {
        ll val[6];
        char sep;
        while(cin >> val[0]){
            for(int i = 1; i < 6; i++) cin >> sep >> val[i];
            x.push_back(val[0]);
            y.push_back(val[1]);
            z.push_back(val[2]);
            vx.push_back(val[3]);
            vy.push_back(val[4]);
            vz.push_back(val[5]);
        }
    }
    int n = sz(x);
    int ans = 0;
    for(int i = 0; i < n; i++){
        for(int j = i+1; j < n; j++){
            lll det = vx[j] * vy[i] - vy[j] * vx[i];
            lll dx = x[j] - x[i], dy = y[j] - y[i];
            if(det != 0){
                lll td = (vx[j] * dy - vy[j] * dx);
                lll sd = (vx[i] * dy - vy[i] * dx);
                // check if paths cross in future
                if(sign(td) * sign(det) < 0 || sign(sd) * sign(det) < 0) continue;
                lll mx = (low - x[i]) * det, Mx = (high - x[i]) * det;
                lll my = (low - y[i]) * det, My = (high - y[i]) * det;
                if(det < 0) swap(mx, Mx), swap(my, My);
                lll px = td * vx[i], py = td * vy[i];
                // check if paths cross inside
                if(px < mx || px > Mx || py < my || py > My) continue;
                ans++;
            }
            else{
                // check if identical
                if(dx * vy[i] - dy * vx[i] != 0) continue;
                assert(false);
                // seems like no two lines are identical!
                
                // if((sign(vx[i]) == sign(vx[j]) && sign(vy[i]) == sign(vy[j])) ||
                //    (sign(vx[i]) == sign(dx) && sign(vy[i]) == sign(dy)))
                //     ans++;
            }
        }
    }
    cout << ans << "\n";
}