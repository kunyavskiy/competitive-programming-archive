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

using namespace std;

typedef long long int64;
typedef long double ld;

struct rmq{

	#define lf(x) ((x)<<1)
	#define rg(x) (((x)<<1)|1)
	#define par(x) ((x)>>1)

	int* tree;
	int* data;
	int n,lst,sz;
	
	void build(vector<int>& data){
		sort(data.begin(),data.end());
		data.erase(unique(data.begin(),data.end()),data.end());
		n = data.size();
		this->data = new int[n];
		copy(data.begin(),data.end(),this->data);
		lst = 2;
		for (;lst < n;lst <<= 1);
		sz = 2*lst - 1;
		tree = new int[sz+10];
		memset(tree,-1,sizeof(int)*(sz+10));
		tree[1] = 0;		
	}
	
	int _get(int pos){
		int v = 1;
		int l = 0,r = lst-1;
		for (;;){
			if (tree[v] != -1)
				return tree[v];
			if ((l+r)/2 >= pos)
				v = lf(v),r = (l+r)/2;
			else
				v = rg(v),l = (l+r)/2+1;
		}
	}
	
	int get(int y){
		return _get(lower_bound(data,data+n,y) - data);
	}
	
	void update(int v,int l,int r,int L,int R,int val){
		if (r < L || R < l || L>R)
			return;
		if (L <= l && r <= R){
			tree[v] = val;
			return;
		}
		if (tree[v] != -1){
			tree[lf(v)] = tree[v];
			tree[rg(v)] = tree[v];			
			tree[v] = -1;
		}
		update(lf(v),l,(l+r)/2,L,R,val);
		update(rg(v),(l+r)/2+1,r,L,R,val);
	}
	
	void update(int l,int r,int val){
		update(1,0,lst-1,lower_bound(data,data+n,l) - data,upper_bound(data,data+n,r)-data-1,val);
	}
	
	#undef lf
	#undef rg
	#undef par
} rmq1,rmq2;

map<pair<int,int>,int> number;
pair<int,int> numpts[210000];

int getnumber(const pair<int,int>& a){
	if (number.find(a) == number.end()){
		int temp = number.size();
		numpts[temp] = a;
		return number[a] = temp;
	}
	return number[a];		
}

pair<int,int> pts[210000],ptr;


vector<int> g[210000];
int d[210000];
int p[210000];

vector<pair<int,int> > ans;

void gen(int v){
	if (v == 0)
		return;	
	int to = p[v];
	gen(to);
	ans.pb(mp(0,numpts[v].second - numpts[to].second));
	ans.pb(mp(numpts[v].first - numpts[to].first,0));
}

void dijkstra(){
	int n = number.size();
	set<pair<int,int> > temp;
	memset(p,-1,sizeof(p));
	temp.insert(mp(0,0));
	for (int i=0;i<n;i++)
		d[i] = 1<<30;
	d[0] = 0;
	for (;;){
		int v = temp.begin()->second;
		if (v == 1)
			break;
		temp.erase(temp.begin());
		for (int i=0;i<g[v].size();i++){
			int to = g[v][i];
			int len = abs(numpts[v].first - numpts[to].first) + abs(numpts[v].second - numpts[to].second);
//			cerr << v <<" "<<to <<" "<<len << endl;
			if (d[to] > d[v] + len){
				temp.erase(mp(d[to],to));
				d[to] = d[v] + len;
				p[to] = v;
				temp.insert(mp(d[to],to));
			}
		}
	}
	printf("%d\n",d[1]);
	gen(1);
	while (ans[0] == mp(0,0))
		ans.erase(ans.begin());
	n = ans.size();		
	for (int i = 1;i<n;i++){
		if (ans[i] == mp(0,0)){
			ans[i] = ans[i-1];
			continue;
		}
		if ((ans[i].first == 0 && ans[i-1].first == 0) || (ans[i].second == 0 && ans[i-1].second == 0))
			ans[i] = ans[i-1] = mp(ans[i].first + ans[i-1].first,ans[i].second + ans[i-1].second);	
	}
	ans.erase(unique(ans.begin(),ans.end()),ans.end());
	n = ans.size();
	printf("%d\n",n);
	for (int i=0;i<n;i++)
		printf("%d %d\n",ans[i].first,ans[i].second);
}


int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
	pts[0] = pts[0] = mp(0,0);
	scanf("%d %d",&pts[1].first,&pts[1].second);
	getnumber(pts[0]);getnumber(pts[1]);
	int n;
	scanf("%d",&n);
	for (int i=0;i<n;i++){
		scanf("%d %d",&pts[2*i+2].first,&pts[2*i+2].second);
		scanf("%d %d",&pts[2*i+3].first,&pts[2*i+3].second);
		pts[2*i+2].first = max(pts[2*i+2].first,pts[2*i+3].first)+1;
		pts[2*i+3].first = pts[2*i+2].first;		
		if (pts[2*i+2].second > pts[2*i+3].second)
			swap(pts[2*i+2],pts[2*i+3]);
		pts[2*i+2].second--;
		pts[2*i+3].second++;
	}
	
	int temp = pts[1].second;
	pts[1].second = (1<<30);	
	sort(pts,pts+2*n+2); 
	n = 2*n+2;
	
	for (int i=0;i<n;i++)
		if (pts[i].second == (1<<30))
			pts[i].second = temp;
	{
		vector<int> ys;
		for (int i=0;i<n;i++)
			ys.pb(pts[i].second);
		rmq1.build(ys);
		rmq2.build(ys);
	}
	
	
	for (int i=0;;i+=2){
		int a = getnumber(pts[i]);
		if (a == 0){
			rmq1.update(-10000000,10000000,0);
			rmq2.update(-10000000,10000000,0);			
			--i;
			continue;
		}
		if (a == 1){
			g[a].pb(rmq1.get(pts[i].second));
			g[g[a].back()].pb(a);
			g[a].pb(rmq2.get(pts[i].second));
			g[g[a].back()].pb(a);
			break;
		}
		int b = getnumber(pts[i+1]);
		
	//	cerr << pts[i].first <<" "<<pts[i].second << endl;
	//	cerr << pts[i+1].first <<" "<<pts[i+1].second << endl;
		
		assert(pts[i].first == pts[i+1].first);
		
		g[a].pb(rmq1.get(pts[i].second));
		g[g[a].back()].pb(a);
		g[a].pb(rmq2.get(pts[i].second));
		g[g[a].back()].pb(a);
		
		g[b].pb(rmq1.get(pts[i+1].second));
		g[g[b].back()].pb(b);
		g[b].pb(rmq2.get(pts[i+1].second));
		g[g[b].back()].pb(b);		
		
		rmq1.update(pts[i].second+1,pts[i+1].second-1,a);
		rmq2.update(pts[i].second+1,pts[i+1].second-1,b);
	}
	
/*	for (int i=0;i<number.size();i++){
		cerr<<numpts[i].first <<" "<<numpts[i].second <<" : ";
		for (int j=0;j<g[i].size();j++)
			cerr << g[i][j] << " ";
		cerr << endl;
	}*/
		
	
	
	dijkstra();
	return 0;
}