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
#define list botva
#define setval(a,v) memset(a,v,sizeof(a))
using namespace std;

const int maxlist=1<<20;
const int maxsz=2*maxlist;
const int maxn=1000100;

int tree[maxsz];
int p[maxn];
int len[maxn];
int lf[maxn];
int64 kol[maxn];
int64 kolone[maxn];
int list,size;
int n;

void update(int v){
	for (v>>=1;v>0;v>>=1)
		tree[v]=tree[2*v]+tree[2*v+1];
}

void use(int v){
	if (v==1 || kolone[v-1]==0)
		tree[v+list-1]=1;
	if (v!=n && kolone[v+1]!=0)
		tree[v+list]=0;
	v+=list-1;
	update(v);
	if (v!=size)
		update(v+1);
}

int find_t(int num){
	int v=1;
	for (;v<list;){
		if (tree[2*v]>=num)
			v=2*v;
		else
			{
				num-=tree[2*v];
				v=2*v+1;
			}
	}
	return v-list+1;
}

int root(int v){
	if (p[v]==v)
		return v;
	return p[v]=root(p[v]);
}

void uni(int a,int b){
	a=root(a);
	b=root(b);
	if (rand()&1)
		swap(a,b);
	p[a]=b;
	len[b]+=len[a];
	lf[b]=min(lf[b],lf[a]);
	kol[b]+=kol[a];
}

void init(){
	list=1;
	for (;list<n;list*=2);
	size=2*list-1;
	for (int i=1;i<=n;i++)
	{
		p[i]=lf[i]=i;
		kol[i]=kolone[i]=0;
	}
}

inline void towers(){
	printf("%d towers\n",tree[1]);	
	return;
}

inline void cubes(int t){
	int tmp=find_t(t);
	printf("%lld cubes in %dth tower\n",kol[root(tmp)],t);
	return;
}

inline void tcubes(int t,int x){
	int tmp=find_t(t)+x-1;
	printf("%lld cubes in %dth column of %dth tower\n",kolone[tmp],x,t);
	return;
}

inline void length(int t){
	int tmp=find_t(t);
	printf("length of %dth tower is %d\n",t,len[root(tmp)]);
	return;	
}

inline void put(int x,int c){
	if (kolone[x]==0)
	{
		use(x);
		kolone[x]=c;
		kol[x]=c;
		len[x]=1;
		if (x!=0 && kolone[x-1]!=0)
			uni(x,x-1);
		if (x!=n && kolone[x+1]!=0)
			uni(x,x+1);		
		return;
	}
	kolone[x]+=c;
	kol[root(x)]+=c;
	return;
}

inline void tput(int t,int x,int c){
	int tmp=find_t(t)+x-1;
	kolone[tmp]+=c;
	kol[root(tmp)]+=c;
	return;
}

char comand[1000];

inline void docomand(){
	gets(comand);
	int par1,par2,par3;
	if (sscanf(comand,"put %d %d",&par1,&par2)==2){
			put(par1,par2);
			return;
		}
	if (sscanf(comand,"cubes %d",&par1)==1){
		cubes(par1);
		return;
	}
	if (sscanf(comand,"length %d",&par1)==1){
		length(par1);
		return;
	}
	if (sscanf(comand,"tput %d %d %d",&par1,&par2,&par3)==3){
		tput(par1,par2,par3);
		return;
	}
	if (sscanf(comand,"tcubes %d %d",&par1,&par2)==2){
		tcubes(par1,par2);
		return;
	}
	towers();
	return;
}


int main()
{
  #ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
  ::n=1000000;
  int n;
	scanf("%d\n",&n);
	init();
	for (int i=0;i<n;i++)
		docomand();

  return 0;
}