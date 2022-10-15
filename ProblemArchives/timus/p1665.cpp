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
    #undef assert
    #define assert(x) if (!(x)) throw 1
#endif

using namespace std;

typedef long long ll;
typedef long double ld;


void solve(){
    int n;
    scanf("%d",&n);
    int cnt = 0;
    for (; n % 2 == 0; n /= 2)
        cnt++;
    for (int i = 3; i*i <= n; i++)
        if (n % i == 0){
            printf("YES\n");
            return;
        }
    if ((n == 1) ^ (cnt % 2 == 0))
        printf("YES\n");
    else
        printf("NO\n");
        
}

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
    int t;
    scanf("%d",&t);
    for (int i = 0; i < t; i++)
        solve();

    return 0;
}