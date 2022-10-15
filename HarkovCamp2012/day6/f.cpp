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

#define taskname "f"

const int inf = 1000000000;
const ld eps = 1e-9;
const int MAXN = 1000100;

vector<int> g[MAXN];
int c[MAXN];
int ans[MAXN];
int p[MAXN];
int anc[MAXN];
int rank[MAXN];
int last[MAXN];

int root(int v){
	if (p[v] == v)
		return v;
	return p[v] = root(p[v]);
}

void join(int a,int b){
	a = root(a);
	b = root(b);
	if (rank[a] > rank[b]){
		p[b] = a;		
	}
	else {
		p[a] = b;
		anc[b] = anc[a];
		if (rank[a] == rank[b])
			rank[b]++;
	}
}

void dfs(int v){
	ans[v] = 1;
	for (int i = 0; i < (int)g[v].size(); i++){
		dfs(g[v][i]);
		ans[v] += ans[g[v][i]];
		join(v,g[v][i]);
	}
	if (last[c[v]] != -1)
		ans[anc[root(last[c[v]])]]--;	
	last[c[v]] = v;
}

int main(){
  freopen(taskname".in","r",stdin);
  freopen(taskname".out","w",stdout);
  int n;
  scanf("%d",&n);
  int r = -1;
  for (int i = 0; i < n; i++){
	 int p;
	 scanf("%d %d",&p,&c[i]);
	 --p;
	 if (p == -1)
	 	r = i;
	 else
	 	g[p].pb(i);
  }

  for (int i = 0; i < n; i++)
  	p[i] = anc[i] = i, rank[i] = 1;

  memset(last,-1,sizeof(last));
  dfs(r);

  for (int i = 0; i < n; i++)
  	printf("%d ",ans[i]);
  return 0;
}

