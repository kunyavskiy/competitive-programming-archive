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

int n,m;


bool used[110000];
int a[110000];


int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
    scanf("%d %d",&n,&m);
    for (int i = 0; i < m; i++){
        scanf("%d",&a[i]);
    }
    sort(a,a+m);

    for (int i = 0; i < m; i++){
        if (a[i] && !used[a[i]-1])
            used[a[i]-1] = true;
        else if (a[i] != n && !used[a[i]])
            used[a[i]] = true;
        else {
            printf("NO\n");
            return 0;
        }            
    }
    printf("YES\n");
    return 0;
}