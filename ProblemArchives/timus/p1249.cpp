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

int last[3100];
int cur[3100];

int n,m;


int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

    scanf("%d %d",&n,&m);

    for (int i = 0 ; i < n; i++){
        for (int j = 0; j < m; j++)
            scanf("%d",&cur[j]);

        if (i){
            for (int j = 1; j < m; j++){
                int cnt = cur[j] + cur[j-1] + last[j] + last[j-1];
                if (cnt == 3)
                {
                    printf("No\n");
                    return 0;                    
                }                       
            }
        }

        memcpy(last,cur,sizeof(int)*m);
    }

    printf("Yes\n");

    return 0;
}