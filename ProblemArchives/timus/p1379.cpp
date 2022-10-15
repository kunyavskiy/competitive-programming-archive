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

const int MAXN = 510;

vector<int> g[MAXN];
vector<int> l[MAXN];
vector<int> w[MAXN];


int d[MAXN];
bool used[MAXN];
int n;

bool can(int mw){
    memset(d,0x3f,sizeof(d));
    memset(used,0,sizeof(used));
    d[0] = 0;

    for (int i = 0; i < n; i++){
        int id = min_element(d,d+n) - d;
        used[id] = true;

        if (id == n-1)
            return d[id] <= 1440;
        if (d[id] == 0x3f3f3f3f)
            return false;

        for (int i = 0; i < (int)g[id].size(); i++){
            if (used[g[id][i]] || w[id][i] < mw)
                continue;
            d[g[id][i]] = min(d[g[id][i]], d[id] + l[id][i]);
        }
        d[id] = 0x3f3f3f3f;
    }
    assert(false);
}


int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

    int m;
    scanf("%d %d",&n,&m);
    for (int i = 0; i < m; i++){
        int a,b,c,d;
        scanf("%d %d %d %d",&a,&b,&c,&d);
        --a,--b;
        if (d < 3000100)
            continue;
        d = d - 3000000;
        d /= 100;
        g[a].pb(b);l[a].pb(c);w[a].pb(d);
        g[b].pb(a);l[b].pb(c);w[b].pb(d);
    }

    int l = 0;
    int r = 10000001;

    while (r - l > 1){
        int mid = (l+r)/2;
        if (can(mid))
            l = mid;
        else
            r = mid;
    }

    cout << l << endl;

    return 0;
}