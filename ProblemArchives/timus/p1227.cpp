//#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <map>
#include <cstring>
#include <string>
#include <cmath>
#include <cassert>
#include <ctime>
#include <algorithm>
#include <sstream>
#include <list>
#include <queue>
#include <deque>
#include <stack>
#include <cstdlib>
#include <cstdio>
#include <iterator>
#include <functional>
#include <bitset>
#define mp make_pair
#define pb push_back

#ifdef LOCAL
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
#else
#define eprintf(...)
#endif

#if ( _WIN32 || __WIN32__ )
    #define LLD "%I64d"
#else
    #define LLD "%lld"
#endif

using namespace std;

#define TASKNAME "1227"

typedef long long ll;
typedef long double ld;

const int MAXN = 11000;

int n,m;
vector<int> g[MAXN];
vector<int> len[MAXN];
vector<int> id[MAXN];

int d[MAXN];
int used[MAXN];
int S;


void dfs(int v,int p,int l){
	if (used[v] || l >= S){
		printf("YES\n");
		exit(0); 
	}
	used[v] = 1;
	d[v] = l;
	for (int i = 0; i < (int)g[v].size(); i++)
		if (id[v][i] != p)
			dfs(g[v][i],id[v][i], l + len[v][i]);
}

int main(){
  #ifdef LOCAL
    freopen(TASKNAME".in","r",stdin);
    freopen(TASKNAME".out","w",stdout);
  #endif
  	
    scanf("%d %d %d",&n,&m,&S);

    for (int i = 0; i < m; i++){
    	int a,b,l;
    	scanf("%d %d %d",&a,&b,&l);
    	--a,--b;
    	g[a].pb(b);
    	g[b].pb(a);
    	len[a].pb(l);
    	len[b].pb(l);
    	id[a].pb(i);
    	id[b].pb(i);
    }

    for (int i = 0; i < n; i++){
    	memset(used,0,sizeof(used));
    	dfs(i,-1,0);
    }

    printf("NO\n"); 
    return 0;
}