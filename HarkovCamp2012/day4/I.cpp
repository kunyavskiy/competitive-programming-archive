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

#define taskname "i"

const int inf = 1000000000;
const ld eps = 1e-9;

const int MAXN = 510000;
vector<int> g[MAXN];

int best,val;

void dfs(int v,int p,int h){
	if (h > val){
		best = v;
		val = h;
	}

	for (int i = 0; i < (int)g[v].size(); i++)
		if (g[v][i] != p)
			dfs(g[v][i],v,h+1);
}


int n,m;


int main(){
  freopen(taskname".in","r",stdin);
  freopen(taskname".out","w",stdout);
  scanf("%d %d",&n,&m);

  for (int i = 0; i < n-1; i++){
  	int a,b;
  	scanf("%d %d",&a,&b);
  	--a,--b;
  	g[a].pb(b);
  	g[b].pb(a);
  }

  val = -1;
  dfs(0,-1,0);
  int temp = best;
  val = -1;
  dfs(temp,-1,0);
  cout << min(n,min(m+1,val+1+max(0,(m-val))/2)) << endl;
  return 0;
}                 

