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

#if ( _WIN32 || __WIN32__ )
    #define LLD "%I64d"
#else
    #define LLD "%lld"
#endif

using namespace std;

typedef long long ll;
typedef long double ld;


void solve(){
    int n,c;
    scanf("%d %d",&n,&c);
    for (int i = 0; i < n; i++){
        int a;
        scanf("%d",&a);
        c -= a;
    }
    if (c >= 0)
        printf("Yes\n");
    else
        printf("No\n");
}

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

    int t;
    scanf("%d",&t);

    for (;t-->0;){
        solve();
    }           
    return 0;
}