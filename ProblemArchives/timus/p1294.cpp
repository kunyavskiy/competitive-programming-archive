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


int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
    ll a,b,c,d;
    cin >> a >> b >> c >> d;
    
    ll ch = a*a+b*b-c*c-d*d;
    ll zn = 2*(a*b-c*d);



    if (zn == 0 || abs(ch) >= abs(zn)){
        cout << "Impossible." << endl;
        return 0;
    }
    
    ld x = sqrt(a*a+b*b - 2*a*b/(ld)zn*ch);

    
    printf("Distance is %d km.\n",(int)(x*1000+0.5));

    return 0;
}