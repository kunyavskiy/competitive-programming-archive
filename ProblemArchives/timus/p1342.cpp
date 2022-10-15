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

double ans[1010][1010];

int n,m;


int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

    scanf("%d %d",&n,&m);

    for (int i = 0; i <= n; i++)
        for (int j = 0; j <= m; j++)
            ans[i][j] = 1e100;

    ans[0][0] = 0;

    for (int i = 0; i < n; i++){
        int k;
        double p,q;
        cin >> k >> p >> q;
        double delta = (q-p)/(k-1);
        double sum = 0;
        for (int j = 0; j <= k; j++){
            for (int s = 0; s <= m-j && ans[i][s] <= 1e50; s++)
                ans[i+1][s+j] = min(ans[i+1][s+j],ans[i][s] + sum);
            sum += p;
            p += delta; 
        }
    }

    for (int i = m; i >= 0; i--){
        if (ans[n][i] < 1e50){
            if (i != m)
                printf("Maximum possible amount: %d\n",i);
            printf("Minimum possible cost: %.2lf\n",ans[n][i]);
            return 0;            
        }
    }

    return 0;
}