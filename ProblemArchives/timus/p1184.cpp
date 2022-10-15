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

int a[11000];


int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
    int n,k;
    scanf("%d %d",&n,&k);

    for (int i = 0; i < n; i++){
        int a , b;
        scanf("%d.%d",&a,&b);
        ::a[i] = 100*a+b;
    }

    int l = 0;
    int r = 1e9;

    while (r - l > 1){
        int mid = (l+r)/2;
        int cnt = 0;
        for (int i = 0; i < n; i++)
            cnt += a[i] / mid;
        if (cnt >= k)
            l = mid;
        else
            r = mid;            
    }

    printf("%d.%02d",l/100,l%100);

    return 0;
}