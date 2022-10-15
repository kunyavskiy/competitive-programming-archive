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

    int w,d;

    scanf("%d %d",&w,&d);

    int L,R,F,B;
    L = F = 0;
    R = w;
    B = d;

    int x0,y0;
    int x1,y1;
    scanf("%d %d",&x0,&y0);
    scanf("%d %d",&x1,&y1);

    char c;
    while (scanf(" %c",&c) != EOF){
        if (c == 'L'){
            R = 2*L - R;
            x1 = 2*L - x1;
        } else if (c == 'R'){
            L = 2*R - L;
            x1 = 2*R - x1;
        } else if (c == 'F'){
            B = 2*F - B;
            y1 = 2*F - y1;
        } else if (c == 'B'){
            F = 2*B - F;
            y1 = 2*B - y1;
        } else {
           assert(0); 
        }
    }

    cout.precision(15);
    cout << sqrt((x0-x1)*1LL*(x0-x1)+(y0-y1)*1LL*(y0-y1)) << endl;
    return 0;
}