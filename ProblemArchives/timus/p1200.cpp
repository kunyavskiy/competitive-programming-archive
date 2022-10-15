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


ll read(){               
    double d;
    scanf("%lf",&d);
    if (d < 0)
        return -10000;
    return ll(d*100+0.5);
}

ll a,b,k;

ll x,y;
ll v;

void check(ll x,ll y){
    if (x + y > k || x < 0 || y < 0)
        return;

    ll c = x*(a-100*x) + y*(b-100*y);


    if (c > v || (c == v && x < ::x) || (c == v && x == ::x && y < ::y)){
        v = c;
        ::x = x;
        ::y = y;
    }
    
}

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

   a = read(),b = read();
   scanf("%d",&k);
   
   x = y = v = 0;

   for (int i = 0; i <= k; i++){
    check(i,k-i);
    check(i,0);
    check(i,b/200);
    check(i,b/200+1);
   }                           

   printf(LLD".%02d\n",(v/100),(int)(v%100));

   cout << x <<" "<<y<<endl;


   return 0;
}