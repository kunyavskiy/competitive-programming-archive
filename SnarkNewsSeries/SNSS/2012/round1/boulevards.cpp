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

#define taskname "boulevards"

using namespace std;

typedef long long int64;
typedef long double ld;

const int MAXN = 2100;

int d1[MAXN];
int d2[MAXN];
int d3[MAXN];
vector<int> g[MAXN];
vector<int> l[MAXN];
int n,m;

void dijkstra(int v,int* d){
    for (int i = 0; i < n; i++)
        d[i] = (1<<30);
    d[v] = 0;
    set<pair<int,int> > s;
    s.insert(mp(0,v));

    for (;!s.empty();){
        int v = s.begin()->second;
        s.erase(s.begin());
        for (int i = 0; i < (int)g[v].size(); i++){
            int to = g[v][i];
            int l = ::l[v][i];
            if (d[to] > d[v] + l){
                s.erase(mp(d[to],to));
                d[to] = d[v] + l;
                s.insert(mp(d[to],to));
            }
        }
    }
}


int main(){
    #ifdef LOCAL
        #ifndef taskname
            #error taskname is not defined
        #else
            freopen(taskname".in","r",stdin);
            freopen(taskname".out","w",stdout);
        #endif
    #endif

    int t = 0;
    scanf("%d",&t);
    while (t-->0){
        scanf("%d %d",&n,&m);
        for (int i = 0; i < n; i++)
            g[i].clear(),l[i].clear();

        int u,v,w;
        scanf("%d %d %d",&u,&v,&w);

        for (int i = 0; i < m; i++){
            int a,b,c;
            scanf("%d %d %d",&a,&b,&c);
            g[a].pb(b);
            g[b].pb(a);
            l[a].pb(c);
            l[b].pb(c);
        }

        dijkstra(u,d1);
        dijkstra(v,d2);
        dijkstra(w,d3);

        int ans = 0;

        for (int i = 0; i < n; i++)
            if (d1[i] + d2[i] == d1[v] && d1[i] + d3[i] == d1[w])
                ans = max(ans,d1[i]);
        cout << ans << endl;
    }


    return 0;
} 