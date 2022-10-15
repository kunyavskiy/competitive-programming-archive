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

const int MAXN = 210000;

vector<int> l[MAXN];
vector<int> g[MAXN];

int n,m;

int d[MAXN];


int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

    scanf("%d %d",&n,&m);
    for (int i = 0; i < m; i++){
        int a,b;
        scanf("%d %d",&a,&b);
        --a,--b;
        g[2*a].pb(2*b);l[2*a].pb(0);
        g[2*b+1].pb(2*a+1);l[2*b+1].pb(0);
    }

    for (int i = 0; i < n; i++){
        g[2*i].pb(2*i+1);
        l[2*i].pb(1);
        g[2*i+1].pb(2*i);
        l[2*i+1].pb(1);
    }


    memset(d,63,sizeof(d));
    int s,e;
    scanf("%d %d",&s,&e);
    --s,--e;

    d[2*s] = d[2*s+1] = 0;

    deque<int> q;
    q.push_back(2*s);
    q.push_back(2*s+1);

    while (!q.empty()){
        int v = q.front();
        q.pop_front();

        if (v == 2*e || v == 2*e+1){
            printf("%d\n",d[v]);
            return 0;
        }

        for (int i = 0; i < (int)g[v].size(); i++)
            if (d[g[v][i]] > d[v] + l[v][i]){
                d[g[v][i]] = d[v] + l[v][i];
                if (l[v][i] == 0)
                    q.push_front(g[v][i]);
                else
                    q.push_back(g[v][i]);
            }
    }

    assert(false);

    return 0;
}