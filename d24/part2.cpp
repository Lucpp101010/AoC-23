#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using lll = __int128_t;
#define sz(x) (int)size(x)

constexpr ll range = 500;

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
    for(ll wx = -range; wx <= range; wx++){
        for(ll wy = -range; wy <= range; wy++){
            for(ll wz = -range; wz <= range; wz++){
                // calculate intersection points of lines 0 and 1 if velocity is changed by wx, wy, wz
                lll px, py, pz;
                {
                    ll dx = x[1] - x[0], dy = y[1] - y[0];
                    ll vx0 = vx[0] - wx, vy0 = vy[0] - wy, vz0 = vz[0] - wz;
                    ll vx1 = vx[1] - wx, vy1 = vy[1] - wy, vz1 = vz[1] - wz;
                    lll det = vx1 * vy0 - vx0 * vy1;
                    if(det == 0) continue;
                    lll td = vx1 * dy - vy1 * dx;
                    lll sd = vx0 * dy - vy0 * dx;
                    px = vx0 * td;
                    py = vy0 * td;
                    pz = vz0 * td;
                    lll pz2 = vz1 * sd;
                    if(px % det != 0 || py % det != 0 || pz % det != 0 || pz2 % det != 0) continue;
                    px /= det;
                    py /= det;
                    pz /= det;
                    pz2 /= det;
                    px += x[0];
                    py += y[0];
                    pz += z[0];
                    pz2 += z[1];
                    if(pz != pz2) continue;
                }
                // check if point is on all lines (with positive t)
                bool bad = false;
                for(int i = 0; i < n; i++){
                    lll dx = px - x[i], dy = py - y[i], dz = pz - z[i];
                    ll vx0 = vx[i] - wx, vy0 = vy[i] - wy, vz0 = vz[i] - wz;
                    if(sign(dx) * sign(vx0) < 0){ // t < 0
                        bad = true;
                        break;
                    }
                    if(dx * vy0 != dy * vx0 || dy * vz0 != dz * vy0){ // not on line
                        bad = true;
                        break;
                    }
                }
                if(bad) continue;
                cout << (ll)px << " " << (ll)py << " " << (ll)pz << "\n";
                cout << wx << " " << wy << " " << wz << "\n";
                cout << "sum: " << (ll)(px + py + pz) << "\n";
                return 0;
            }
        }
    }
    cout << "No solution found :(\n";
}