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

int g[110][110];

int n,m;
int have[110];
int start[110];


int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

    memset(g,63,sizeof(g));

    scanf("%d %d",&n,&m);
    

    for (int i = 0; i < m; i++){
        int l;
        vector<int> v;
        scanf("%d",&l);
        v.resize(l);
        for (int j = 0; j < l; j++)
            scanf("%d",&v[j]),v[j]--;
        for (int j = 0; j < l; j++)
            for (int k = 0; k < l; k++)
                g[v[j]][v[k]] = 4;
    }

    int k;
    scanf("%d",&k);

    for (int i = 0; i < n; i++)
        g[i][i] = 0;
    
    for (int i = 0; i < k; i++){
        int t;
        scanf("%d %d %d",&have[i],&start[i],&t);
        start[i]--;
        if (t) have[i] = 1<<20;
    }

    for (int l = 0; l < n; l++)
        for(int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                g[i][j] = min(g[i][j],g[i][l] + g[l][j]);


    int to = -1,sum = 1<<30;

    for (int i = 0; i < n; i++){
        bool ok;
        int cur;
        ok = 1, cur = 0;
        for (int j = 0; j < k; j++)
            if (g[i][start[j]] > have[j])
                ok = false;
            else
                cur += g[i][start[j]] * (have[j] <= 1000);
        if (ok){
            if (sum > cur)
                to = i, sum = cur;
        }

    }

    if (to == -1)
        printf("0\n");
    else
        printf("%d %d\n",to+1,sum);


    return 0;
}