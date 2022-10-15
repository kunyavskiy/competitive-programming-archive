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
typedef short int sint;

sint dp[2010][2010];  

int val[2010],n;
int id[2010];

pair<int,int> temp[2010];
                    

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

    scanf("%d",&n);

    for (int i = 0; i < n; i++){
        scanf("%d",&temp[i].first);
        temp[i].second = i+1;
    }

    sort(temp,temp+n);

    int n1 = 0;

    for (int i = 0; i < n; i++)
        if (!i || temp[i].first != temp[i-1].first)
            val[n1] = temp[i].first, id[n1] = temp[i].second, n1++;

    n = n1;

    
    if (n == 1){
        printf("1\n1\n");
        return 0;
    }

    int ans = 2;
    int f = 0;
    int s = 1;

    for (int i = n-1; i >= 0; i--){
        int ptr = i;

        for (int j = i+1; j < n && ptr < n; j++){
            while (ptr < n && val[ptr] < 2*val[j] - val[i])
                ptr++;
            if (ptr == n)
                break;
            if (val[ptr] == 2*val[j] - val[i])
                dp[i][j] = 1 + max((sint)2,dp[j][ptr]);

            if (dp[i][j] > ans){
                ans = dp[i][j];
                f = i;
                s = j;
            }                           
        }               
    }


    vector<int> res;
    res.pb(id[f]);
    res.pb(id[s]);

    for (int i = s+1; i < n; i++)
        if (val[i] == 2*val[s] - val[f]){
            f = s;
            s = i;
            res.pb(id[i]);
        }

    printf("%d\n",res.size());
    for (int i = 0; i < (int)res.size(); i++)
        printf("%d ",res[i]);
    

    return 0;
}