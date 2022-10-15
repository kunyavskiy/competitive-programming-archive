#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <queue>
#include <deque>
#include <stack>
#include <algorithm>
#include <memory.h>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <iterator>

#define mp make_pair
#define pb push_back

#ifdef LOCAL
    #define LLD "%I64d"
#else
    #define LLD "%lld"
#endif

#define taskname "balance"

using namespace std;

typedef long long int64;
typedef long double ld;

const int MAXN = 5000000;

int a[MAXN];
int ml[MAXN];
int Ml[MAXN];
int mr[MAXN];
int Mr[MAXN];
int n;

int main(){
    #ifdef LOCAL
        #ifndef taskname
            #error taskname is not defined
        #else
            freopen(taskname".in","r",stdin);
            freopen(taskname".out","w",stdout);
        #endif
    #endif

    while (true){
        scanf("%d",&n);
        if (n == 1)
            break;
        for (int i = 0; i < n; i++){
            scanf("%d",&a[i]);
        }
        ml[0] = Ml[0] = a[0];
        for (int i = 1; i < n; i++){
            ml[i] = min(ml[i-1],a[i]);
            Ml[i] = max(Ml[i-1],a[i]);
        }
        mr[n-1] = Mr[n-1] = a[n-1];

        for (int i = n-2; i >= 0; i--){
            mr[i] = min(mr[i+1],a[i]);
            Mr[i] = max(Mr[i+1],a[i]);
        }

        int k = 0;
        for (int i = 1; i < n-1; i++){
            if (max(Mr[k+1] - mr[k+1],Ml[k] - ml[k]) > max(Mr[i+1] - mr[i+1], Ml[i] - ml[i]))
                k = i;
        }
        printf("%d\n",k+1);
    }
    return 0;
} 