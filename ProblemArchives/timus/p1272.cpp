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

int p[11000];

int get(int v){
    if (p[v] == v)
        return v;
    return p[v] = get(p[v]);
}

void join(int u,int v){
    p[get(u)] = get(v);
}



int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

    int n,m,k;
    scanf("%d %d %d",&n,&m,&k);
    for (int i = 0; i < n; i++)
        p[i] = i;
    for (int i = 0; i < m; i++){
        int a,b;
        scanf("%d %d",&a,&b);
        --a,--b;
        join(a,b);
    }

    int ans = 0;
    for (int i = 0; i < k; i++){
        int a,b;
        scanf("%d %d",&a,&b);
        --a,--b;
        if (get(a) != get(b))
            ans++;
        join(a,b);
    }

    cout << ans << endl;

    return 0;
}