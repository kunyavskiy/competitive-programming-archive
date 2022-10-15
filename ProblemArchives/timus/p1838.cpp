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

int len,n;
int a[110000];


int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
    scanf("%d %d",&len,&n);
    for (int i = 0; i < n; i++)
        scanf("%d",&a[i]);

    int ans = 0;

    for (int i = 1; i < n; i++){
        int l = a[i-1];
        int r = a[i];

        l = max(l,2*a[0]);
        r = min(r,2*a[i-1]);

        l = max(l,2*a[i] - len); 
        r = min(r,2*a[n-1] - len);

        //cerr << l <<" "<<r<<endl;

        ans += max(0, r - l);
    }

    cout << len - ans << endl;
    return 0;
}