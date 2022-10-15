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
    #undef assert
    #define assert(x) if (!(x)) throw 1
#endif

using namespace std;

typedef long long ll;
typedef long double ld;

ld myatan2(ld y,ld x){
    ld ang = atan2(y,x);
    if (ang < -(1e-9))
        ang += 2*M_PI;
    return ang;
}


ld get(ld d,ld r1,ld r2){
    if (r1 > r2)
       swap(r1,r2);
    if (r1 + r2 < d+(1e-9))
        return 0;
    if (r2 - r1 > d-(1e-9))
        return M_PI*r1*r1;

    ld x = (r1*r1 - r2*r2 + d*d)/(2*d);

    ld a = sqrt(r1*r1 - x*x);

    ld sa = a/r1;
    ld ca = x/r1;

    ld sb = a/r2;
    ld cb = (d-x)/r2;
    

    return myatan2(sa,ca)*r1*r1  + myatan2(sb,cb)*r2*r2 - d*a;
}

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
    ld d,r1,r2,r3,r4;

    cin >> d >> r2 >> r1 >> r4 >> r3;
    cerr.precision(15);

    cout.precision(15);
/*    cerr << (r1*r1+r3*r3-r2*r2-r4*r4) << endl; 
    cerr << (get(d,r1,r3))/M_PI<<endl;
    cerr << (get(d,r1,r4))/M_PI<<endl;
    cerr << (get(d,r2,r3))/M_PI<<endl;
    cerr << (get(d,r2,r4))/M_PI<<endl;*/
    cout << fixed << (r1*r1+r3*r3-r2*r2-r4*r4)*M_PI-(get(d,r1,r3) - get(d,r1,r4) - get(d,r2,r3) +get(d,r2,r4)) <<endl;
    return 0;
}