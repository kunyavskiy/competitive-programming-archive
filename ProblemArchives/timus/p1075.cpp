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

ld a[3];
ld b[3];
ld c[3];

ld d1,d2,d3;
ld r;


int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
    
    int n = 3;
    for (int i = 0; i < n; i++){
       cin >> a[i];
    }
    for (int i = 0; i < n; i++){
       cin >> b[i];
    }          
    for (int i = 0; i < n; i++){
       cin >> c[i];
    }

    for (int i = 0; i < n; i++){
        d1 += (a[i] - c[i])*(a[i] - c[i]);
        d2 += (b[i] - c[i])*(b[i] - c[i]);
        d3 += (a[i] - b[i])*(a[i] - b[i]);
    }

    d1 = sqrt(d1);
    d2 = sqrt(d2);
    d3 = sqrt(d3);
    
    cin >> r;

    ld angC = acos((d1*d1 + d2*d2 - d3*d3)/(2*d1*d2));
    ld ang1 = acos(r/d1);
    ld ang2 = acos(r/d2);

    ld ans = 0;

    if (ang1 + ang2 < angC)
       ans = sqrt(d1*d1-r*r) + sqrt(d2*d2-r*r) + r*(angC - ang1 - ang2);
    else
       ans = d3;

    

    cout.precision(15);
    cout << fixed << ans << endl;
    return 0;
}