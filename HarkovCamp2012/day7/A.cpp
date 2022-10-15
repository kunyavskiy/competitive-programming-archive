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

#define taskname "a"

const int MAXN = 110000;

vector<int> g[MAXN];
vector<int> l[MAXN];
vector<int> num[MAXN];
int n,m;

int a[MAXN];
int k;

int d[MAXN];


void dijkstra(int start){
	for (int i = 0; i < n; i++)
		d[i] = int(1e9)+100;
	d[start] = 0;
	set<pair<int,int> > s;
	s.insert(mp(0,start));

	while (!s.empty()){
	    int v = s.begin()->second;
	    s.erase(s.begin());
	    for (int i = 0; i < (int)g[v].size(); i++){
	    	int to = g[v][i];
	    	if (d[to] > d[v] + l[v][i]){
	    	    s.erase(mp(d[to],to));
	    	    d[to] = d[v] + l[v][i];
	    	    s.insert(mp(d[to],to));
	    	}	    		
	    }	    	
	}	
}

bool cmp(int v,int u){
	return d[v] < d[u];
}

vector<int> ans;
bool used[MAXN];

bool dfs(int v,int to){
	if (v == to)
		return true;	
	if (d[v] >= d[to])
		return false;
	used[v] = true;

	for (int i = 0; i < (int)g[v].size(); i++){
		if (d[g[v][i]] != d[v] + l[v][i])
			continue;
		if (used[g[v][i]])
			continue;
		ans.pb(num[v][i]);
		if (dfs(g[v][i],to))
			return true;
		ans.pop_back();
	}

	return false;
}



int main(){
  freopen(taskname".in","r",stdin);
  freopen(taskname".out","w",stdout);

  scanf("%d %d",&n,&m);

  for (int i = 0; i < m; i++){
  	int a,b,c;
  	scanf("%d %d %d",&a,&b,&c);
  	--a,--b;
  	g[a].pb(b);
  	g[b].pb(a);
  	l[a].pb(c);
  	l[b].pb(c);
  	num[a].pb(i+1);
  	num[b].pb(i+1);
  }

  scanf("%d",&k);

  for (int i = 0; i < k; i++)
  	scanf("%d",&a[i]),--a[i];


  dijkstra(a[0]);
  int md = 0;
  int v = -1;

  for (int i = 0; i < k; i++)
  	md = max(md,d[a[i]]);

  for (int i = 0; i < k; i++)
  	if (d[a[i]] == md)
  		v = a[i];
	
  dijkstra(v);

 
  sort(a,a+k,cmp);


  for (int i = 0; i < k; i++)
  	dfs(a[i],a[i+1]);

  printf("%d\n",(int)ans.size());

  for (int i = 0; i < (int)ans.size(); i++)
  	printf("%d ",ans[i]);
  return 0;
}

