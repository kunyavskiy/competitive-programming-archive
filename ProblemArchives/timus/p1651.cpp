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


int a[110000];
int n;

int best[110000];
int prev[110000];
int len[110000];

void gen(int v){
    if (v == -1)
        return;
    gen(prev[v]);
    printf("%d ",a[v]);
}



int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

    scanf("%d",&n);
    for (int i = 0; i < n; i++)
        scanf("%d",&a[i]);

    memset(len,63,sizeof(len));

    len[a[0]] = 0;
    prev[0] = -1;
    best[a[0]] = 0;

    for (int i = 1; i < n; i++){
        if (len[a[i]] > len[a[i-1]] + 1){
            len[a[i]] = len[a[i-1]] + 1;
            prev[i] = best[a[i-1]];
            best[a[i]] = i;
        }
    }

    gen(best[a[n-1]]);

    return 0;
}