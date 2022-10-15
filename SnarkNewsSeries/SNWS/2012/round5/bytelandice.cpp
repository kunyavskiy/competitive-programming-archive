#include <iostream>
#include <cassert>
#include <fstream>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <queue>
#include <deque>
#include <stack>
#include <algorithm>
#include <memory.h>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <iterator>

#define mp make_pair
#define pb push_back

#ifdef LOCAL
	#define LLD "%I64d"
#else
	#define LLD "%lld"
#endif

#define taskname "bytelandice"

using namespace std;

typedef long long ll;
typedef long double ld;

int n;
ll s,d,t;
ll a,b,c,e;

ll dp[30][30][30][30];


ll get(int a,int b,int c,int e){
    if (a < 0 || b < 0 || c < 0 || e < 0)
        return 1<<30;
    ll& ans = dp[a][b][c][e];
    if (a == 0 && b == 0 && c == 0 && e == 0)
        return ans = 0;
    if (ans != -1)
        return ans;
    ans = 1LL<<60;

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            for (int k = 0; k < 3; k++)
                for (int l = 0; l < 3; l++){
                    if (k && j) continue;
                    if (k && l) continue;
                    if (i && l) continue;
                    if (i+j+k+l > 3) continue;
                    if (i+j+k+l == 0) continue;                        
                    ans = min(ans,get(a-i,b-j,c-k,e-l)+s*(i+j+k+l==1)+d*(i+j+k+l==2)+t*(i+j+k+l==3));
                }
   // cerr << a <<" "<<b<<" "<<c<<" "<<e<<" ->"<<ans<<endl;
    return ans;
}


int main(){
	#ifndef taskname
		#error taskname is not defined
	#else
		freopen(taskname".in","r",stdin);
		freopen(taskname".out","w",stdout);
	#endif

       cin >> n >> s >> d >> t;

       assert(6*s > 3*d && 3*d > 2*t);
       assert(s < d && d < t);
//       assert(2*d >= t+s);

       for (int i = 0; i < n; i++){
          int x,y;
          cin >> x >> y;
          if (x && y)
            a += x, b += y;
          else
            c += x, e += y;
       }

       ll ans = 0;


       memset(dp,-1,sizeof(dp));

       while (a >= 30) ans += t, a -= 3;
       while (b >= 30) ans += t, b -= 3;
       while (c >= 30) ans += t, c -= 3;
       while (e >= 30) ans += t, e -= 3;

       ans += get(a,b,c,e);

       cout << ans << endl;
       return 0;
} 