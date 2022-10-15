#ifndef LOCAL
    #pragma comment(linker, "/STACK:33554432")
#endif

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

#ifdef LOCAL
    #define LLD "%I64d"
#else
    #define LLD "%lld"
    #define M_PI 3.1415926535897932384626433832795
    #define prev prev_dsfdfgfhgfh
    #define next next_mkdlsmfdgkl
    #define hash hash_mdfdsgdhgfm
    #undef assert
    #define assert(x) if (!(x)) throw 1
    #define sqrt(x) sqrt((double)(x))
#endif

using namespace std;

typedef long long ll;
typedef long double ld;

ll x,y;
int B,K;

ll c[40][40];

ll calc(ll r){
   // cerr << r << endl;
    ll x = 1;
    int st = 0;
    while (x <= r){
        x *= B;
        st++;
    }

    ll ans = 0;

    int k = K;

    while (true){
        //cerr << k <<" "<<x<<" "<<st<<" "<<r<<" "<<ans<<endl;
        if (k == 0){
           ans++;
           break;
        }
        if (st == -1)
            break;
        if (x > r){
            --st;
            x /= B;
            continue;
        }
        ans += c[st][k];
        r -= x;
        x /= B;
        --st;
        --k;
    }
   // cerr << ans << endl<<endl;;
    return ans;
}

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif



  cin >> x >> y >> K >> B;

  c[0][0] = 1;

  for (int i = 0; i < 40; i++)
    for (int j = 0; j < 40; j++){
         if (i) c[i][j] += c[i-1][j];
         if (i && j) c[i][j] += c[i-1][j-1];            
    }



  cout << calc(y) - calc(x-1) << endl;                 

  return 0;
}