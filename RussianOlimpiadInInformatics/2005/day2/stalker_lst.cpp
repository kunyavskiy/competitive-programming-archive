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
typedef short int sint;

struct node{
	sint to;
	node* next;
};


const int MAXN=2001;
const int MAXK=2001;

node* g[2001][2001];
int d[2001][2001];
int mind[2001];
int n,k;

void add(int a,int b,int c){
	node* tmp = new node;
	tmp->to = a;
	tmp->next = g[b][c];
	g[b][c] = tmp;
	tmp = new node;
	tmp->to = b;
	tmp->next = g[a][c];
	g[a][c] = tmp;
}

sint deqmem[2*MAXN*MAXK*2+500];
int deqmemptr;

struct deq{
	sint* data;
	int h,t;
	int sz;
	inline void init(){
		data = deqmem + deqmemptr;
		sz=n*k+100;
		deqmemptr+=sz;
		h=t=0;
	}
	inline bool empty(){
		return h==t;
	}
	inline void push_back(sint v){
		data[t]=v;
		++t;
		if (t==sz)
			t=0;		
	}
	inline void push_front(sint v){
		--h;
		if (h==-1)
			h=sz-1;
		data[h]=v;
	}
	inline int front(){
		return data[h];
	}
	inline void pop_front(){
		++h;
		if (h==sz)
			h=0;
	}	
	
} dc,dv;


void bfs(){
	dc.init();
	dv.init();	
	for (int i=0;i<n;i++){
		mind[i]=(1<<14);
		for (int j=0;j<k;j++)
			d[i][j]=(1<<14);
	}
	for (int i=0;i<k;i++){
		d[0][i]=1;
		dc.push_back(i);
		dv.push_back(0);
	}
	
	
	for (;!dc.empty();){
		int v=dv.front();dv.pop_front();
		int c=dc.front();dc.pop_front();
		if (v==n-1){
			printf("%d\n",d[v][c]);
			return;
		}
		for (node* it = g[v][c];it;it=it->next){
			if (d[it->to][c] > d[v][c]){
				d[it->to][c] = d[v][c];
				dc.push_front(c);
				dv.push_front(it->to);				
			}
		}
		if (mind[v] > d[v][c]){
			mind[v] = d[v][c];
			for (int i=0;i<k;i++){
				if (d[v][i] > d[v][c] + 1){
					d[v][i] = d[v][c] + 1;
					dc.push_back(i);
					dv.push_back(v);
				}
			}
		}
	}
	printf("-1\n");
	return;		
}


void readgraf(int col){
	int m;
	scanf("%d",&m);
	int a,b;
	for (int j=0;j<m;j++){
		scanf("%d %d",&a,&b);
		--a,--b;		
	//	g[a][col].pb(b);
	//	g[b][col].pb(a);
		add(a,b,col);
	}
}


int main()
{
//    freopen("stalker.in","r",stdin);
  //  freopen("stalker.out","w",stdout);
	scanf("%d %d",&n,&k);
	for (int i=0;i<k;i++)
		readgraf(i);
	bfs();	
	return 0;
}