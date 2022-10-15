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

#define lf first
#define rg second

using namespace std;

typedef long long int64;
typedef long double ld;

struct edge{
	int to,time,num;
};

struct segment{
	int l,r;	
};

vector<edge> g[2200];
vector<segment> bad[110000];
vector<int> badend[110000];
edge edges[110000];
int n,m,k;

void merge(vector<segment>& s,segment t){
	for (;s.size() && s.back().l >= t.l;s.pop_back());
	if (s.size() && s.back().r >= t.l){
		s.back().r = t.r;
	}
	else
		s.pb(t);
}

int from[2200];
int d[2200];
int fromedge[2200];
bool used[2200];

void gen(int n,int cnt){
	if (n == 0){
		printf("%d\n",cnt);
		return;
	}
	gen(from[n],cnt+1);
	printf("%d ",fromedge[n]+1);
}


int main()
{
//	freopen("redhat.in","r",stdin);
//	freopen("redhat.out","w",stdout);
	scanf("%d %d %d",&n,&m,&k);
	for (int i=0;i<m;i++){
		edge tmp;
		int a,b,t;
		scanf("%d %d %d",&a,&b,&t);
		a--,b--;
		tmp.num = i;
		tmp.time = t;
		tmp.to = b;
		g[a].pb(tmp);
		tmp.to = a;
		g[b].pb(tmp);
		edges[i] = tmp;
	}
	int T = 0;
	for (int i=0;i<k;i++){
		int num,t;
		scanf("%d %d",&num,&t);
		--num;
		segment s;
		s.l = T - edges[num].time;
		s.r = T + t;
		T+=t;
		merge(bad[num],s);
	}
	for (int i=0;i<m;i++){
		badend[i].reserve(bad[i].size()*2);
		for (int j=0;j<bad[i].size();j++){
			badend[i].pb(bad[i][j].l);
			badend[i].pb(bad[i][j].r);
		}
	}
	for (int i=0;i<n;i++)
		d[i] = T;
	d[0] = 0;
	for (int i=0;i<n;i++){
		int v = -1;
		for (int j=0;j<n;j++)
			if (!used[j] && (v == -1 || d[v] > d[j]))
				v = j;
	//	cerr<<v<<" "<<d[v]<<endl;
		if (v== -1)
			break;
		used[v] = true;
		for (int i=0;i<g[v].size();i++){
			int tmp = upper_bound(badend[g[v][i].num].begin(),badend[g[v][i].num].end(),d[v])-badend[g[v][i].num].begin();
			int start = d[v];
			if (tmp%2 == 1)
				start = badend[g[v][i].num][tmp];
			if (d[g[v][i].to] > start + g[v][i].time){
				d[g[v][i].to] = start + g[v][i].time;
				from[g[v][i].to] = v;
				fromedge[g[v][i].to] = g[v][i].num;
			}
		}
	}
	
	if (d[n-1] == T)
		printf("NO\n");
	else{
		printf("YES\n");
		gen(n-1,0);
		printf("\n");
	}	
	return 0;
}