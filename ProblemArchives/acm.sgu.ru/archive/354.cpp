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
#define rg(x) (((x)+1)<<1)
#define par(x) (((x)-1)>>1)
using namespace std;

int top[600][600];
int lft[600][600];

int fr[600*600+10];
int sr[600*600+10];

int n;

void error(){
	printf("0\n");
	exit(0);
}

struct node{
	int v,d;
};

node tree[1<<11];
int lst,sz;
const int inf=1<<25;

void init(int* inv){
	lst=1;
	for (;lst<n;lst<<=1);
	sz=2*lst;
	for (int i=0;i<n;i++)
	{
		tree[i+lst-1].v=inv[i];
		tree[i+lst-1].d=0;
	}
	for (int i=n;i<lst;i++)
	{
		tree[i+lst-1].v=inf;
		tree[i+lst-1].d=0;
	}	
	for (int i=lst-2;i>=0;i--)
	{
		tree[i].d=0;
		tree[i].v=min(tree[lf(i)].v,tree[rg(i)].v);
	}
}

void push(int v){
	tree[lf(v)].d+=tree[v].d;
	tree[rg(v)].d+=tree[v].d;
	tree[lf(v)].v-=tree[v].d;
	tree[rg(v)].v-=tree[v].d;
	tree[v].d=0;
}

void update(int v){
	tree[v].v=min(tree[lf(v)].v,tree[rg(v)].v);
	tree[v].v-=tree[v].d;
}

int find_right(){
	if (tree[0].v!=0)
		error();
	int tmp=0;
	for (;tmp<lst-1;){
		push(tmp);
		if (tree[rg(tmp)].v==0)
			tmp=rg(tmp);
		else
			tmp=lf(tmp);
	}
	return tmp-lst+1;
}

void update_inf(int v){
	v=v+lst-1;
	tree[v].v=inf;	
	tree[v].d=0;
	for (v=par(v);v;v=par(v))
		update(v);
	if (lst!=1)
		update(0);
}

void update(int v,int l,int r,int L,int R){
	if (r<L || l>R || r<l)
		return;
	if (l>=L && r<=R)
		{
			tree[v].v--;
			tree[v].d++;
			return;
		}
	push(v);
	update(lf(v),l,(l+r)/2,L,R);
	update(rg(v),(l+r)/2+1,r,L,R);
	update(v);
	return;
}

void gen(int* inv,int* p)
{
	init(inv);
	for (int i=n;i>0;i--){
		int tmp=find_right();
		p[tmp]=i;
		update_inf(tmp);
		update(0,0,lst-1,tmp+1,n-1);	
	}
};

void horisontal(int i){
	int p[600];
	setval(p,0);
	
	gen(lft[i],p);	
	
//	cerr<<i<<endl;
//	for (int j=0;j<n;j++)
//		cerr<<p[j]<<" \n"[j==n-1];

	int pr[601];
	for (int j=0;j<n;j++)
		pr[p[j]]=j;
	
	for (int j=2;j<=n;j++)
		fr[i*n+pr[j]]=i*n+pr[j-1];
}

int used[600*600+10];

void vertical(int j){
	int p[600];
	setval(p,0);
	int inv[600];
	
	for (int i=0;i<n;i++)
		inv[i]=top[i][j];
	
	gen(inv,p);
	
	
//	cerr<<j<<endl;
//	for (int i=0;i<n;i++)
//		cerr<<p[i]<<" \n"[i==n-1];
	
	int pr[601];
	for (int i=0;i<n;i++)
		pr[p[i]]=i;
	
	for (int i=2;i<=n;i++)
		sr[pr[i]*n+j]=pr[i-1]*n+j;
}

int ans[600][600];

void dfs(int v){
	static int counter=1;
	if (used[v]==1)
		error();
	if (used[v]==2)
		return;
	used[v]=1;
	if (fr[v]!=-1)
		dfs(fr[v]);
	if (sr[v]!=-1)
		dfs(sr[v]);
	ans[v/n][v%n]=counter++;	
	used[v]=2;
}

int main()
{
  #ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
  setval(fr,-1);
  setval(sr,-1);
  scanf("%d",&n);
  for (int i=0;i<n;i++)
  	for (int j=0;j<n;j++)
  		scanf("%d",&top[i][j]);
  for (int i=0;i<n;i++)
  	for (int j=0;j<n;j++)
  		scanf("%d",&lft[i][j]);
 
  for (int i=0;i<n;i++)
  	{
  		horisontal(i);
  	//	cerr<<i<<endl;
  		vertical(i);
  	//	cerr<<i<<endl;
  	}
  for (int i=0;i<n*n;i++)
  		dfs(i);
  for (int i=0;i<n;i++)
  {
  	for (int j=0;j<n;j++)
  		printf("%d ",ans[i][j]);
  	printf("\n");
  }
  return 0;
}