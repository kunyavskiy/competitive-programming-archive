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


const int MAXN = 11111;

int a[MAXN];           
vector<int> g[MAXN];
int n;

int get(int x){
    int cnt = 0;
    for (int i = 0; i < (int)g[x].size(); i++)
        if (a[x] == a[g[x][i]])
            cnt++;
    return cnt;
}

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

    int n;
    scanf("%d",&n);

    for (int i = 0; i < n; i++){
        int k;
        scanf("%d",&k);
        g[i].resize(k);
        for (int j = 0; j < k; j++)
            scanf("%d",&g[i][j]),--g[i][j];
    }

    bool q = true;
    while (q){
        q = false;
        for (int i = 0; i < n; i++)
            if (get(i) > 1)
                a[i] ^= 1, q = true;
    }

    vector<int> v1,v2;
    for (int i = 0; i < n; i++)
        if (a[i])
            v1.pb(i);
        else
            v2.pb(i);

    if (v1.size() > v2.size())
        swap(v1,v2);
    if (v1.size() == v2.size() && v2[0] == 0)
        swap(v1,v2);

    printf("%d\n",v1.size());

    for (int i = 0; i < (int)v1.size(); i++)
        printf("%d ",v1[i]+1);

    return 0;
}