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
#define int64 long long
#define ld long double  
#define setval(a,v) memset(a,v,sizeof(a))

#define lf(x) (((x)<<1)+1)
#define rg(x) (((x+1)<<1))
#define par(x) ((x-1)>>1)
using namespace std;

const int maxn=60100;
const int maxlst=1<<17;
const int maxsz=maxlst*2;

int xs[maxn*2];

int tree[maxsz];

int sz,lst;

void update(int v){
	if (tree[lf(v)]==tree[rg(v)])
		tree[v]=tree[lf(v)];
	else
		tree[v]=-1;	
}

void push(int v){
	if (tree[v]==-1)
		return;
	tree[lf(v)]=tree[v];
	tree[rg(v)]=tree[v];
	tree[v]=-1;
}

void update(int v,int l,int r,int L,int R,int d){
	if (r<L || l>R)
		return;
	if (l>=L && r<=R){
		tree[v]=d;
		return;
	}
	push(v);
	update(lf(v),l,(l+r)/2,L,R,d);
	update(rg(v),(l+r)/2+1,r,L,R,d);
	update(v);
	return;
}

int val(int v,int l,int r,int V){
	if (tree[v]!=-1)
		return tree[v]; 
	if (V<=(l+r)/2)
		return val(lf(v),l,(l+r)/2,V);
	else
		return val(rg(v),(l+r)/2+1,r,V);
}

void init(int n){
	lst=1;
	for (;lst<n;lst<<=1);
	sz=2*lst-1;
	setval(tree,0);
}

struct event{
	int y;
	int xl,xr;
	bool st;
	int num;
	event(int Y=-1,int Xl=-1,int Xr=-1,int Num=-1,bool s=false){
		y=Y;
		xl=Xl;
		xr=Xr;
		st=s;
		num=Num;
	}
};

bool operator<(const event& a,const event& b){
	return a.y<b.y || (a.y==b.y && a.st && !b.st);
}

event evs[maxn*2];

int64 s[maxn];
int par[maxn];


int main()
{
  #ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
  int n;
  scanf("%d",&n);
  int w,h;
  scanf("%d %d",&w,&h);
  int ptr=0;
  xs[ptr]=0;
  evs[ptr++]=event(0,0,w,0,true);
  xs[ptr]=w;
  evs[ptr++]=event(h,0,w,0,false);
  s[0]=h*1ll*w;
  for (int i=0;i<n;i++){
  	int x1,x2,y1,y2;
  	scanf("%d %d %d %d",&x1,&y1,&x2,&y2);
  	if (x1>x2)
  		swap(x1,x2);
  	if (y1>y2)
  		swap(y1,y2);
  	xs[ptr]=x1;
  	evs[ptr++]=event(y1,x1,x2,i+1,true);
  	xs[ptr]=x2;
  	evs[ptr++]=event(y2,x1,x2,i+1,false);
  	s[i+1]=(y2-y1)*1ll*(x2-x1);  	
  }
  
  sort(evs,evs+ptr);
  sort(xs,xs+ptr);
  int xkol=unique(xs,xs+ptr)-xs; 
  
  init(xkol);
  
  for (int i=0;i<ptr;i++){
  	int nv;
  	if (evs[i].st){
  		int pos=lower_bound(xs,xs+xkol,evs[i].xl)-xs;
	  	int tmp=val(0,0,lst-1,pos);
	  	if (evs[i].num!=0)
	  		s[tmp]-=s[evs[i].num];  		
  		nv=evs[i].num;
  		par[nv]=tmp;
  	}
  	else
  		nv=par[evs[i].num];
	 	int l=lower_bound(xs,xs+xkol,evs[i].xl)-xs;
	 	int r=lower_bound(xs,xs+xkol,evs[i].xr)-xs;
  	update(0,0,lst-1,l,r,nv);
   }
  
 
    
  sort(s,s+n+1);
  
  for (int i=0;i<=n;i++)
  	cout<<s[i]<<" ";
  cout<<endl;  
  return 0;
}