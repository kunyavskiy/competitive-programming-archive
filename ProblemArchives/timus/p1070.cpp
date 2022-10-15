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


int gettime(){
    int h,m;
    scanf("%d.%d",&h,&m);
    return h*60+m;
}


int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
           
     int t1 = gettime();
     t1 = gettime() - t1;

     int t2 = gettime();
     t2 = gettime() - t2;
                                     
     if (t1 < 0)
        t1 = 24*60 + t1;
     if (t2 < 0)
        t2 = 24*60 + t2;
     
     if (t1 > 16*60)
        t1 -= 24*60;

     if (t2 > 16*60)
        t2 -= 24*60;
     //cerr << t1 <<" "<<t2<<endl;

     int t = (int)(abs((t1-t2)/120.0)+0.5);


     cout << t << endl;

    return 0;
}