#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <cmath>
#include <cassert>
#include <ctime>
#include <algorithm>
#include <queue>
#include <memory.h>
#include <stack>
#define mp make_pair
#define pb push_back                     
#define setval(a,v) memset(a,v,sizeof(a))

#if ( _WIN32 || __WIN32__ )
    #define LLD "%I64d"
#else
    #define LLD "%lld"
#endif

using namespace std;

typedef long long ll;
typedef long double ld;


const int MOD = 1000000007;

ll ans;

ll w,h;

ll even(ll l,ll r){
    if (l % 2)
        l++;
    if (r % 2)
        r--;
    if (l > r) return 0;
    return (r - l)/2 + 1;
}

ll odd(ll l,ll r){
    return r - l + 1 - even(l,r);
}

ll odd(ll x){
    return odd(0,x);
}

ll even(ll x){
    return even(0,x);
}


ll intersec(ll a,ll b,ll c,ll d){
    return max(0LL , min(b,d) - max(a,c) + 1);
}

ll solve(int dx,int dy){
   ll res = 0;
   for (int i1 = 0; i1 < 2; i1++)
      for (int i2 = 0; i2 < 2; i2++)
         for (int i3 = 0; i3 < 2; i3++)
            for (int i4 = 0; i4 < 2; i4++)
                if ((((i1^dx) & (i4 ^ dy)) ^ ((i3 ^ dx) & (i2 ^ dy))) == 0) {
                    ll cnt = 1;
                    cnt = (cnt * (i1?odd(w):even(w))) % MOD;
                    cnt = (cnt * (i2?odd(h):even(h))) % MOD;
                    cnt = (cnt * (i3?odd(w):even(w))) % MOD;
                    cnt = (cnt * (i4?odd(h):even(h))) % MOD;
                    res += cnt;
                }

    int res2 = 0;
    for (int i = 0; i <= w; i++)
        for (int j = 0; j <= h; j++)
            for (int i1 = 0; i1 <= w; i1++)
                for (int j1 = 0; j1 <= h; j1++){
                    int t = (i - dx) * (j1 - dy) - (j - dy) * (i1 - dx);
                    res2 += (t % 2 == 0);
                }
    assert(res == res2);
    //cerr <<"!!!"<<res << endl;
    return res % MOD;
}

ll solve2(int i,int j,int k){
    int ldx = min(i,k*i);
    int ldy = min(j,k*j);
    int rdx = max(i,k*i);
    int rdy = max(j,k*j);
    //cerr << i <<" "<<j<<" "<<k<<"    "<< (intersec(0,w,-ldx,w-rdx) * intersec(0,h,-ldy,h-rdy)) % MOD  << endl;
    //cerr << intersec(0,w,-ldx,w-rdx) <<" "<< intersec(0,h,-ldy,h-rdy) << endl;
    ll res =  (intersec(0,w,-ldx,w-rdx) * intersec(0,h,-ldy,h-rdy)) % MOD; 
    ll res2 = 0;
    for (int i1 = 0; i1 <= w; i1++)
        for (int j1 = 0; j1 <= h; j1++){
            bool q = true;
            q &= 0 <= i*k + i1;
            q &= 0 <= i + i1;
            q &= i*k + i1 <= w;
            q &= i + i1 <= w;
            
            q &= 0 <= j*k + j1;
            q &= 0 <= j + j1;
            q &= j*k + j1 <= h;
            q &= j + j1 <= h;

            res2 += q;
        }
    assert(res2 == res);
    return res2;
}


int main(){

  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
    ans = 0;

    cin >> w >> h;

    ans += (MOD - ((w+1)*(h+1)) % MOD);

    ans += odd(w) * odd(h) * solve(1,1);
    ans += odd(w) * even(h) * solve(1,0);
    ans += even(w) * odd(h) * solve(0,1);
    ans += even(w) * even(h) * solve(0,0);

    ans %= MOD;

    cerr << ans << endl;

    ans += (MOD - (w *  h *  (h-1) * (h-1))) % MOD;

    for (int i = -w; i <= w; i++)
        if (i)
          for (int k = 1; abs(k*i) <= w; k++)
              for (int j = 0; j*k <= h; j++){
                  ans += MOD - solve2(i,j,k);
                  if (j) ans += MOD - solve2(i,-j,k);
                  ans += MOD - solve2(i,j,-k);
                  if (j) ans += MOD - solve2(i,-j,-k);
                  ans %= MOD;
                  if (!k) break;
              }

    cerr << ans << endl;

    ans += MOD - ((w+1)*(h+1) * ((w+1)*(h+1)-1) * 4) % MOD;


    ans = ((ans % MOD) + MOD)% MOD;

    cout << ans << endl;
      
    return 0;
}