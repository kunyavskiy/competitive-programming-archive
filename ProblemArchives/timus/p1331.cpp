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

#define y1 y1_dfghjkl

using namespace std;

typedef long long ll;
typedef double ld;


ld R;

ld lat1[5100], lon1[5100];
ld lat2[5100], lon2[5100]; 
int n,m;

ld s1[5100],c1[5100],cl1[5100],sl1[5100];
ld s2[5100],c2[5100],cl2[5100],sl2[5100];


int main(){
  #ifdef LOCAL
    freopen("1331.in","r",stdin);
    freopen("1331.out","w",stdout);
  #endif

    scanf("%d %d %lf",&n,&m,&R);

    for (int i = 0; i < m; i++){
        scanf("%lf %lf",&lat1[i],&lon1[i]);
        lat1[i] *= M_PI/180;
        lon1[i] *= M_PI/180;
        s1[i] = sin(lat1[i]);
        c1[i] = cos(lat1[i]);
        sl1[i] = sin(lon1[i]);
        cl1[i] = cos(lon1[i]);
    }
    


    for (int i = 0; i < n; i++) {
        scanf("%lf %lf",&lat2[i],&lon2[i]);
        lat2[i] *= M_PI/180;
        lon2[i] *= M_PI/180;
        s2[i] = sin(lat2[i]);
        c2[i] = cos(lat2[i]);
        sl2[i] = sin(lon2[i]);
        cl2[i] = cos(lon2[i]);
    }

    for (int i = 0; i < n; i++){
    #ifdef LOCAL
       if (i % 100 == 0)
       fprintf(stderr,"%d\n",(int)i);
    #endif
        ld best = -1e10;
        for (int j = 0; j < m; j++){
            ld temp = s1[j]*s2[i] + c1[j]*c2[i]*(cl1[j]*cl2[i] + sl1[j]*sl2[i]);
            if (best < temp)
            	best = temp;
        }
        if (best < -1.0)
        	best = -1.0;
        if (best > 1.0)
        	best = 1.0;
        best = acos(best);
        printf("%.4lf\n",best*R);
    }
    
    #ifdef LOCAL
       fprintf(stderr,"%d",(int)clock());
    #endif

    return 0;
}