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

#if ( _WIN32 || __WIN32__ )
    #define LLD "%I64d"
#else
    #define LLD "%lld"
#endif

using namespace std;

typedef long long ll;
typedef long double ld;

const int MAXN = 110000;

vector<int> g[MAXN];

ll ans;
int n,m;

int tin[MAXN];
int tup[MAXN];
bool used[MAXN];

int bridges;

int dfs(int v,int p){
    assert(!used[v]);
    used[v] = true;
    int cnt = 1;
    static int timer = 0;
    tin[v] = ++timer;
    tup[v] = tin[v];
    for (int i = 0; i < (int)g[v].size(); i++){
        int to = g[v][i];
        if (to == p)
            continue;
        if (used[to]){
            tup[v] = min(tup[v], tin[to]);
            continue;
        }

        int temp = dfs(g[v][i],v);
        if (tup[to] > tin[v]){
            bridges++;
            ans += temp * 1LL * (n-temp) - 1;
        }                                
        cnt += temp;
        tup[v] = min(tup[v],tup[to]);
    }
    return cnt;
}



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
    g[a].pb(b);
    g[b].pb(a);
  }

  memset(used,0,sizeof(used));

  int comp = 0;

  vector<int> sz;

  for (int i = 0; i < n; i++){
    if (!used[i]){
        sz.pb(dfs(i,-1));
        comp++;
    }
  }

  if (comp > 2){
     printf("0\n");
     return 0;
  }

  if (comp == 2){
    ans = (m - bridges)*1LL*sz[0]*1LL*sz[1];
    cout << ans << endl;
    return 0;
  }

  ans += (m-bridges)*1LL*(n*1LL*(n-1)/2 - m);

  cout << ans << endl;
  return 0;
}