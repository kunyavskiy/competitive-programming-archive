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

const int MAXN = 110000;

int color[MAXN];
int p[MAXN];


int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
    int n,q;
    scanf("%d %d",&n,&q);
    for (int i = 0; i < n; i++){
        scanf("%d",&p[i]);
        --p[i];
    }

    int cur = 1;

    for (int i = 0; i < n; i++){
        if (color[i])
            continue;
        if (i > 1)
            cur++;
        for (int j = i; !color[j]; j = p[j])
            color[j] = cur;
    }

    for (int i = 0; i < q; i++){
        int a,b;
        scanf("%d %d",&a,&b);
        --a,--b;
        if (color[a] == color[b])
            printf("Yes\n");
        else
            printf("No\n");
    }

  return 0;
}