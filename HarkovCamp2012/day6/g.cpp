#include <cstdio>
#include <cmath>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <cassert>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <list>
#include <queue>
#include <stack>
#include <deque>
#include <iterator>

#define mp make_pair
#define pb push_back
#define sqr(a) ((a) * (a))
#define zero(a) memset (a, 0, sizeof(a))
#define sz(a) (int)(a.size())

#ifdef LOCAL
	#define LLD "%I64d"
#else 
	#define LLD "%lld"
#endif

using namespace std;

typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
typedef unsigned int uint;

#define taskname "g"

const int inf = 1000000000;
const ld eps = 1e-9;
const int MAXN = 310000;

vector<int> g[MAXN];
int c[MAXN];
int n,m;
int ans[MAXN][10];
int ord[MAXN];
int p[MAXN];
int ptr, l ,r, y;


void dfs(int v){
	for (int i = 0; i < (int)g[v].size(); i++)
		dfs(g[v][i]), ans[v][y]+=ans[g[v][i]][y];
	if (c[v]>=l && c[v]<=r)
	  ans[v][y]++;
}



int main(){
  freopen(taskname".in","r",stdin);
  freopen(taskname".out","w",stdout);

  scanf("%d %d",&n,&m);

  int root = -1;

  for (int i = 0; i < n; i++){

  	scanf("%d %d",&p[i],&c[i]);
  	--p[i];
  	if (p[i] == -1)
  		root = i;
  	else
  		g[p[i]].pb(i);
  }

  ptr = 0;

  for (y = 0; y < m; y++){
  	scanf("%d %d",&l,&r);
  	dfs(root);
  }

  for (int i = 0; i < n; i++)
  	for (int j = 0; j < m; j++)
  		printf("%d%c",ans[i][j]," \n"[j==m-1]); 	
  	

  return 0;
}

