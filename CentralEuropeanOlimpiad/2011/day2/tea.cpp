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

const int MAXN = 1100000;


int p[MAXN];
int rank[MAXN];
int val[MAXN];
int pos[MAXN];
int n;


inline void reset(){	
	for (int i=0;i<=n;i++)
		p[i] = i,rank[i] = 1;	
}

inline void add(int pos,int v){
	val[pos] = v;
	::pos[pos] = pos;	
}

inline int root(int v){
	int temp = v,temp2;
	
	for (;p[v]!=v;v=p[v]);	
	for (;temp!=v;){
		temp2 = p[temp];
		p[temp] = v;
		temp = temp2;
	}
	
	return v;
}

inline void merge(int v,int u){
	v = root(v);
	u = root(u);
	if (rank[v] > rank[u])
		swap(v,u);
	p[v] = u;
	if (val[v] > val[u]){
		val[u] = val[v];
		pos[u] = pos[v];
	}
	if (rank[u] == rank[v])
		rank[u]++;	
}


int t[MAXN];
int prev[MAXN];

struct node{
	int l,to;
	node* next;
};

node mem[MAXN];
node* g[MAXN];
pair<int,int> a[MAXN];
int st[MAXN],stpt;


int calct(int maxlen){
	for (int i=0;i<=n;i++){
		g[i] = 0;	
		t[i] = -(1<<30);
	}
	for (int i=1;i<=n;i++){
		mem[i].l = i - maxlen;
		if (mem[i].l < 0) mem[i].l = 0;
		if (i-a[i-1].first >= 0){
			mem[i].to = i;
			mem[i].next = g[i-a[i-1].first];
			g[i-a[i-1].first] = &mem[i];
		}
		else
			mem[i].next = 0;
	}
	reset();
	t[0] = 0;
	stpt = 0;
	for (int i=0;i<n;i++){
		add(i,t[i]);
		for (;stpt > 0 && t[st[stpt-1]] < t[i];) 
			merge(st[stpt-1],i),--stpt;
		st[stpt++] = i;
		for (node* it = g[i];it;it = it->next){
			t[it->to] = val[root(it->l)]+1;
			prev[it->to] = pos[root(it->l)];
		}
	}
	return t[n];
}

void gen(int n){
	if (n == 0)
		return;
	int j = prev[n];
	printf("%d",n-j);
	for (int i=j+1;i<=n;i++)
		printf(" %d",a[i-1].second+1);
	printf("\n");
	gen(j);		
}




int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
	scanf("%d",&n);
//    n = 1000*1000;
	for (int i=0;i<n;i++){
		scanf("%d",&a[i].first);
/*		if (RAND_MAX > (1<<17))
			a[i].first = rand()%100+1;
		else
			a[i].first = ((((unsigned int)rand())<<16) | ((unsigned int) rand()))%100+1;*/
		a[i].second = i;
	}
	sort(a,a+n);  	
	int ans = calct(n);
	printf("%d\n",ans);
	int l = a[n-1].first-1;
	int r = n;
	for (;r-l > 1;){
		int mid = (l+r)/2;
		int temp = calct(mid);
		if (temp == ans)
			r = mid;
		else
			l = mid;			
	}
	calct(r);
//	cerr << prev[n] << endl;
	gen(n);	
	return 0;
}