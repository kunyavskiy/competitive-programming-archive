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




/*

Message #<n>.
Received at <HH>:<MM>:<SS>. 
Current ship's coordinates are 
<X1>^<X2>'<X3>" <NL/SL> 
and <Y1>^<Y2>'<Y3>" <EL/WL>.
An iceberg was noticed at 
<A1>^<A2>'<A3>" <NL/SL> 
and <B1>^<B2>'<B3>" <EL/WL>. 
=== 

*/

ld getangle(){
    int a,b,c;
    char t;
    scanf("%d^%d'%d\" %cL",&a,&b,&c,&t);
    ld g = a + b/60.0 + (c/60.0)/60.0;
    g = g / 180.0 * M_PI;
    if (t == 'S' || t == 'W')
        g *= -1;
    return g;
}
                      

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

    scanf("%*[^\n]");
    scanf(" %*[^\n]");
    scanf(" %*[^\n]");
    ld fi1 = getangle();
    scanf(" and");
    ld la1 = getangle();
    scanf(". %*[^\n]");
    ld fi2 = getangle();
    scanf(" and");
    ld la2 = getangle();
    scanf(". %*[^\n]");

    ld ans = acos(sin(fi1)*sin(fi2)+cos(fi1)*cos(fi2)*cos(la2-la1));

    ans *= 3437.5;

    printf("The distance to the iceberg: %.2lf miles.\n",(double)ans);

    if(100.00-ans>0.005) 
        printf("DANGER!\n");
    return 0;
}