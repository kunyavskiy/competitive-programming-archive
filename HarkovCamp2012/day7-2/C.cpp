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

#undef assert
#define assert(x) while (!(x));

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

#define taskname "c"

const int MAXN = 110000;
const int MAXLOG = 18;

const int inf = 1000000000;
const ld eps = 1e-9;

vector<int> g[MAXN];
vector<int> gt[MAXN];
int n,q;
int X,A,B,Y,C,D;
vector<int> special;
int h[MAXN];
int p[MAXN];
int sum[MAXN];
int up[MAXLOG][MAXN];
bool used[MAXN];

vector<bool> canfrom[110];
vector<bool> canto[110];


void dfsund(int v,int p,int h,int sum){
	cerr << v <<" "<<p<<endl;
	up[0][v] = p;
	::h[v] = h;
	::sum[v] = sum;
	used[v] = true;

	for (int i = 0; i < (int)g[v].size(); i++){
		int to = g[v][i];
		if (used[to]){
			if (to != p)
				special.pb(v);
			continue;
		}
		dfsund(to,v,h+1,sum+1);
	}

	for (int i = 0; i < (int)gt[v].size(); i++){
		int to = gt[v][i];
		if (used[to]){
			if (to != p)
				special.pb(to);
			continue;
		}
		dfsund(to,v,h+1,sum-1);
	}
}


void dfsfrom(int v,int id){
	if (canfrom[id][v])
		return;
	canfrom[id][v] = true;
	for (int i = 0; i < (int)g[v].size(); i++){
		dfsfrom(g[v][i],id);
	}
}


void dfsto(int v,int id){
	if (canto[id][v])
		return;
	canto[id][v] = true;
	for (int i = 0; i < (int)gt[v].size(); i++)
		dfsto(gt[v][i],id);
}

void initlca(){
	for (int i =1; i<MAXLOG; i++)
	 	for (int j = 0; j < n; j++)
	 		up[i][j] = up[i-1][up[i-1][j]];
}

int getup(int v,int h){
	for (int i = 0; i < MAXLOG; i++)
		if (h & (1<<i))
			v = up[i][v];
	return v;
}

int getlca(int v,int u){
	if (h[v] > h[u])
		swap(v,u);
	u = getup(u,h[u]-h[v]);
//	cerr << "!"<<v <<" "<<u<<endl;
	if (u == v)
		return u;
	for (int i = MAXLOG-1; i >= 0; i--)
		if (up[i][u] != up[i][v])
			u = up[i][u],v = up[i][v];
	return up[0][u];
}

void Precalc(){
	dfsund(0,-1,0,0);
	up[0][0] = 0;
	initlca();

	sort(special.begin(),special.end());
	special.erase(unique(special.begin(),special.end()),special.end());
	assert(special.size() <= 100);

	for (int i = 0; i < (int)special.size(); i++){
//		cerr << special[i] << endl;
		canfrom[i].resize(n);
		dfsfrom(special[i],i);
		canto[i].resize(n);
		dfsto(special[i],i);
	}
}

bool solve(int a,int b){
	for (int j = 0; j < (int)special.size(); j++)
		if (canto[j][a] && canfrom[j][b])
			return true;

	int l = getlca(a,b);
	cerr << l << endl;

	return ((sum[a] - sum[l]) == -(h[l] - h[a])) && ((sum[b] - sum[l]) == -(h[b] - h[l]));
}


int _solve(int a,int b){
	if (a == b)
		return 0;
	if (solve(a,b))
		return 1;
	if (solve(b,a))
		return -1;
	return 0;	
}





int main(){
  freopen(taskname".in","r",stdin);
  freopen(taskname".out","w",stdout);
  scanf("%d %d",&n,&q);
  scanf("%d %d %d",&X,&A,&B);
  scanf("%d %d %d",&Y,&C,&D);

  for (int i = 0; i < n; i++){
  	int k;
  	scanf("%d",&k);
  	for (int j = 0; j < k; j++){
  		int a;
  		scanf("%d",&a);
  		g[i].pb(a);
  		gt[a].pb(i);
  	}
  }


  Precalc();
//  cerr <<"!!!"<<up[1][7] << endl;
//  cerr <<"!!!!"<<endl;

  int x = X,y = Y;
  int sum = 0;

  for (int i = 0; i < q; i++){
  	int cur = _solve(x,y);
  	printf("%d\n",cur);
  	x = (A*1LL*x+B+sum)%n;
  	y = (C*1LL*y+D+sum)%n;
  	sum += abs(cur);
  }
  return 0;
}

