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

#define taskname "building"

using namespace std;

typedef long long int64;
typedef double ld;

const int MAXN = 110;

int xp[MAXN];
int yp[MAXN];
int xr[MAXN];
int yr[MAXN];
int v[MAXN];
int n,m;

int mt[MAXN],bmt[MAXN];
int used[MAXN],usept;
vector<int> g[MAXN];



bool dfs(int v){
    if (used[v] == usept)
        return false;
    used[v] = usept;
    for (int i = 0; i < g[v].size(); i++){
        int to = g[v][i];
        if (mt[to] == -1 || dfs(mt[to])){
            mt[to] = v;
            bmt[v] = to;
            return true;
        }                                
    }
    return false;
}

bool check(ld mid){
    for (int i = 0; i < m; i++)
       g[i].clear();

    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            if (sqrt((xp[i] - xr[j])*(xp[i] - xr[j])+(yp[i] - yr[j])*(yp[i] - yr[j])) <= mid*v[j]+(1e-9))
                g[i].pb(j);
            

    memset(mt,-1,sizeof(mt));
    memset(bmt,-1,sizeof(bmt));
    ++usept;

    for (int i = 0; i < m; i++)
        for (int j = 0; j < g[i].size(); j++)
            if (mt[g[i][j]] == -1){
                mt[g[i][j]] = i;
                bmt[i] = g[i][j];
                break;
            }

    for (int i = 0; i < m; i++){
        if (bmt[i] != -1)
            continue;
        usept++;
        if (!dfs(i))
            return false;        
    }
    return true;
}

void solve(){
    scanf("%d %d",&m,&n);
    int xpr,ypr,xrp,yrp,vpr;

    scanf("%d %d %d",&xpr,&ypr,&vpr);

    for (int i = 0; i < n; i++)
        scanf("%d %d %d",&xr[i],&yr[i],&v[i]);

    ld ans = 0;

    scanf("%d %d",&xrp,&yrp);

    for (int i = 0; i < m; i++)
        scanf("%d %d",&xp[i],&yp[i]);

    ans = ((xpr - xrp)*(xpr-xrp) + (ypr - yrp)*(ypr-yrp))/(ld)(vpr*vpr);


    ld l = 0;
    ld r = 1e10;

    //cerr << ans << endl;

    for (int i = 0; i < 200; i++){
        ld mid = (l+r)/2;
        if (check(mid))
            r = mid;
        else
            l = mid;
    }

    cout.precision(15);
    cout << fixed << ld(l+r)/2+sqrt(ans) << endl;
}


int main(){
	#ifndef taskname
		#error taskname is not defined
	#else
		freopen(taskname".in","r",stdin);
		freopen(taskname".out","w",stdout);
	#endif

       int t;
       scanf("%d",&t);
       for (;t-->0;)
        solve();

	return 0;
} 