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

#define TIMESTAMP(x) eprintf("["#x"] Time : %.3lf s.\n", clock()*1.0/CLOCKS_PER_SEC)
#define TIMESTAMPf(x,...) eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__, clock()*1.0/CLOCKS_PER_SEC)

#if ( _WIN32 || __WIN32__ )
    #define LLD "%I64d"
#else
    #define LLD "%lld"
#endif

using namespace std;

#define TASKNAME "E"

#ifdef LOCAL
static struct __timestamper {
	~__timestamper(){
		TIMESTAMP(end);
	}
} __TIMESTAMPER;
#endif

typedef long long ll;
typedef long double ld;

struct item{
	ll x0, c;
	ll calc(ll x){
		return max(x, x0) - c;
	}
	item(){
		x0 = -(1LL<<55);
		c = 0;
	}
};

item merge(item a,item b){
	item res;
	res.x0 = max(a.x0, b.x0 + a.c);
	res.c = a.c + b.c;
	return res;
}

const int MAXN = 110000;

int x[MAXN];
int v[MAXN];
item tree[3*MAXN];
item res[MAXN];
int n,m,k, lst;

item get(int v,int l,int r,int L,int R){
	if (r < L || R < l) return item();
	if (L <= l && r <= R)
		return tree[v];
	return merge(
	              get(2*v, l, (l+r)/2, L,R),
	              get(2*v+1, (l+r)/2+1, r,L,R)
	            );	
}


void solve(){
	scanf("%d %d %d",&n,&m,&k);
	x[0] = -1, v[0] = -1;
	n++;
	for (int i = 1; i < n; i++)
		scanf("%d %d",&x[i],&v[i]);
	lst = 2;
	while (lst < n) lst *= 2;
	for (int i = 1; i < n; i++){
		tree[i+lst].c = k*1LL*(x[i] - x[i-1]) - v[i];
		tree[i+lst].x0 = k*1LL*(x[i] - x[i-1]);
	}
	for (int i = lst-1; i > 0; i--)
		tree[i] = merge(tree[2*i], tree[2*i+1]);


	for (int i = 0; i < m; i++){
		int L,R;
		ll st;
		scanf("%d %d "LLD,&L,&R,&st);
		int Lid = lower_bound(x,x+n,L) - x;
		int Rid = upper_bound(x,x+n,R) - x;
//		eprintf("%d %d %d %d\n",L,R,Lid,Rid);
		assert(0 < Lid && Lid <= Rid && Rid <= n);
		st += (L - x[Lid-1]) * 1LL* k;
		item f = get(1, 0, lst - 1, Lid, Rid-1);
		st = f.calc(st);
		st -= (R - x[Rid-1]) * 1LL * k;
		printf(LLD"\n", max(st, 0LL));
	}

	
}

int main(){
  #ifdef LOCAL
    freopen(TASKNAME".in","r",stdin);
    freopen(TASKNAME".out","w",stdout);
  #endif

 	int t;
 	scanf("%d",&t);
 	while (t-->0)
 		solve();
 	 
  return 0;
}