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

const int MAXN = 110000;
const int MAXLST = 1<<17;
const int MAXSZ = MAXLST * 2 + 100;

ll tree[MAXSZ];
ll upd[MAXSZ];
int len[MAXSZ];
int a[MAXN];
int lst,sz;

ll ans[MAXN];
int type[MAXN];
int ra[MAXN];
int rb[MAXN];
int rc[MAXN];
int id[MAXN];
int n,m;
vector<int> g[MAXN];

void build(){
	lst = 2;
	for (;lst < n; lst *= 2);
	sz = 2* lst-1;
	for (int i = 0;i < n; i++){
		tree[i+lst] = a[i];
		len[i+lst] = 1;
	}
	for (int i = lst-1; i > 0; i--)
		tree[i] = tree[2*i] + tree[2*i+1],len[i] = len[2*i]+len[2*i+1];
}

void update(int v){
	tree[v] = tree[2*v] + tree[2*v+1];
}

void push(int v){
	upd[2*v] += upd[v];
	upd[2*v+1] += upd[v];
	tree[2*v] += upd[v] * len[2*v];
	tree[2*v+1] += upd[v] * len[2*v+1];
	upd[v] = 0;
}

void update(int v,int l,int r,int L,int R,int c){
	if (R < l || r < L)
		return;
	if (L <= l && r <= R){
		upd[v] += c;
		tree[v] += c*1LL*len[v];
		return;
	}
	push(v);
	update(2*v,l,(l+r)/2,L,R,c);
	update(2*v+1,(l+r)/2+1,r,L,R,c);
	update(v);
}

ll get(int v,int l,int r,int L,int R){
	if (R < l || r < L)
		return 0;
	if (L <= l && r <= R)
		return tree[v];
    push(v);	
	return get(2*v,l,(l+r)/2,L,R)+get(2*v+1,(l+r)/2+1,r,L,R);
}
            

void dfs(int v){
	if (type[v] == 0)
		ans[v] = get(1,0,lst-1,ra[v],rb[v]);
	else if (type[v] == 1)
		update(1,0,lst-1,ra[v],rb[v],rc[v]);

	for (int i = 0; i < (int)g[v].size(); i++)
		dfs(g[v][i]);

	if (type[v] == 1)
		update(1,0,lst-1,ra[v],rb[v],-rc[v]);				
}                                         


int main(){
  freopen(taskname".in","r",stdin);
  freopen(taskname".out","w",stdout);

  scanf("%d %d",&n,&m);
  for (int i = 0; i < n; i++)
	scanf("%d",&a[i]);
  
  build();

  type[0] = 2;

  for (int i = 1; i <= m; i++){
  	char c;
  	scanf(" %c",&c);
  	if (c == '?'){
  		type[i] = 0;
  		scanf("%d %d",&ra[i],&rb[i]);
  		ra[i]--,rb[i]--;
  	}
  	else if (c == '+'){
  		type[i] = 1;
  		scanf("%d %d %d",&ra[i],&rb[i],&rc[i]);
  		ra[i]--,rb[i]--;
  	}else {
  		assert(c == 't');
  		type[i] = 2;
  		scanf("%d",&ra[i]);
  	}
  }

  id[0] = 0;

  for (int i = 1;i <= m; i++){
  	if (type[i] != 2){
  		g[i-1].pb(i);
  		id[i] = i;
  	}
  	else {
  		g[id[ra[i]-1]].pb(i);
  		id[i] = id[ra[i]-1];
  	}
  }

  dfs(0); 

  for (int i = 1; i <= m; i++)
  	if (type[i] == 0)
  		printf(LLD"\n",ans[i]);
  return 0;
}

