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

#define lf(x) ((x)<<1)
#define rg(x) (((x)<<1)|1)
#define par(x) ((x)>>1)

#if ( _WIN32 || __WIN32__ )
	#define LLD "%I64d"
#else
	#define LLD "%lld"
#endif

using namespace std;

typedef long long int64;
typedef long double ld;

const int MAXN = 510000;

const int inf = 1<< 30;

int rcost[MAXN];
int pcost[MAXN];
int size[MAXN];
int nsize[MAXN];
int n,m;

pair<int,int> temp[MAXN];

bool cmpsec(const pair<int,int>& a,const pair<int,int>& b){
	if (a.second != b.second)
		return a.second < b.second;
	return a.first < b.first;
}

bool cmpfirst(const pair<int,int>& a,const pair<int,int>& b){
	if (a.first != b.first)
		return a.first < b.first;
	return a.second < b.second;
}

void read(int n,int* cost,int* size,bool sec){
	for (int i=0;i<n;i++)
		scanf("%d %d",&temp[i].second,&temp[i].first);
	sort(temp,temp+n,sec?cmpsec:cmpfirst);
	for (int i=0;i<n;i++){
		cost[i] = temp[i].second;
		size[i] = temp[i].first;
	}
}


struct rmq{	
	int* tree;
	int* tpos;
	int lst,sz;
	
	void init(int n,int* a){
		lst = 2;
		for (;lst < n;lst <<=1);
		sz= 2*lst - 1;
		tree = new int[sz + 10];
		tpos = new int[sz + 10];
		memcpy(tree+lst,a,n*sizeof(int));
		for (int i = lst+n;i < sz;i++)
			tree[i] = -inf;
		for (int i=0;i<lst;i++)
			tpos[lst+i] = i;
		
		for (int i = lst-1;i>0;--i)
			update(i);
	}
	
	void update(int v,int val){
		v = v+lst;
		tree[v] = val;
		for (v=par(v);v;v=par(v))
			update(v);		
	}
	
	pair<int,int> get(int v,int l,int r,int L,int R);	
		
	int getval(int L,int R){
		return get(1,0,lst-1,L,R).first;		
	}
	
	int getpos(int L,int R){
		return get(1,0,lst-1,L,R).second;		
	}
	
	void getall(int L,int R,int& val,int& pos){
		pair<int,int> res = get(1,0,lst-1,L,R);
		val = res.first;
		pos = res.second;
	}
	
	void update(int v){
		if (tree[lf(v)] > tree[rg(v)]){
			tree[v] = tree[lf(v)];
			tpos[v] = tpos[lf(v)];
		}
		else {
			tree[v] = tree[rg(v)];
			tpos[v] = tpos[rg(v)];
		}		
	}
} rmq1,rmq2;


pair<int,int> rmq::get(int v,int l,int r,int L,int R){
	if (r<L || R<l || R<L)
		return mp(-inf,-inf);
	if (L <= l && r<=R)
		return mp(tree[v],tpos[v]);
	pair<int,int> ans1 = get(lf(v),l,(l+r)/2,L,R);
	pair<int,int> ans2 = get(rg(v),(l+r)/2+1,r,L,R);
	return max(ans1,ans2);	
}

int l[MAXN];
int r[MAXN];

int tempcost[MAXN];
int next[MAXN];
int prev[MAXN];

void deleteroom(int room){
	if (next[room] != n)
		prev[next[room]] = prev[room];
	if (prev[room] != -1)
		next[prev[room]] = next[room];
}




int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
	int o;
	scanf("%d %d %d",&n,&m,&o);
	read(n,rcost,size,true);
	read(m,pcost,nsize,false);
	
	int ptr = 0;
	
	for (int i=0;i<m;i++){
		while (ptr < n && size[ptr] < nsize[i]){
			l[ptr+1] = r[ptr+1] = r[ptr];
			++ptr;
		}
		r[ptr]++;	
	}
	
	for (int i=0;i<n;i++){
		//cerr << l[i] <<" "<<r[i] <<" "<<size[i] << endl;
		next[i] = i+1;
		prev[i] = i-1;
	}
	

	int64 ans = 0;

	rmq1.init(m,pcost);
	
	
	for (int i=0;i<n;i++)
		tempcost[i] = -rcost[i] + rmq1.getval(l[i],r[i]-1);
		
		
	rmq2.init(n,tempcost);
	
//	cerr <<"!!!"<<endl;
	
	for (int i=0;i<o;i++){
		if (rmq2.tree[1] <= 0)
			break;
		ans += rmq2.tree[1];
		int room = rmq2.tpos[1];
		int per = rmq1.getpos(l[room],r[room]-1);
		rmq1.update(per,-inf);
		rmq2.update(room,-inf);
		int nroom = next[room];
		if (nroom != n){		
			l[nroom] = l[room];
			rmq2.update(nroom,-rcost[nroom] + rmq1.getval(l[nroom],r[nroom]-1));
		}
		deleteroom(room);
	}
	
	cout << ans << endl;
		
	return 0;
}