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


int n,m;
ld u,v;

ld ans;
int vans;


int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

    cin >> n >> m >> u >> v;

    ans = (n-1)*u;
    vans = 1;

    for (int i = 2; i <= n; i++){
       ld cans = 0;
       cans = max(v * (m-1) + 15, (n - i) * u);
       cans += 2 * (i - 1) * v + 5;

      // cerr << ans <<" "<<cans << endl;

       if (cans < ans + (1e-9))
          ans = cans, vans = i;    
    }

    cout << vans << endl;

    return 0;
}