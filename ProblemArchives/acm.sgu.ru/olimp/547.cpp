#include <iostream>
#include <iterator>
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
using namespace std;

struct reb{
	int x,y,w;
	bool used;
	int num;
	reb(){
		x=y=w=0;
		used=false;
	}
};

bool operator<(const reb& a,const reb &b){
	if (b.x==0 || b.y==0)
		return false;
	if (a.x==0 || a.y==0)
		return true;
	return a.w<b.w;
}

const int maxn=5100;
const int maxm=100100;

int p[maxn];
int n;

void init(){
	for (int i=0;i<n;i++)
		p[i]=i;
}

int root(int a){
	if (a==p[a])
		return a;
	return p[a]=root(p[a]);
}

bool uni(int a,int b){
	a=root(a);
	b=root(b);
	if (a==b)
		return false;
	if (rand()&1)
		p[a]=b;
	else
		p[b]=a;
	return true;
}

reb gr[maxm];
vector<int> g[maxn];
//int gmat[maxn][maxn];
vector<int> gcomp[maxn];
int compbest[maxn];
//int compbestcomp[maxn];
int rootreb[maxn];
int comp[maxn];
bool exist[maxn];
int compn,m;

void dfs(int v,int com){
	comp[v]=com;
	int sz=g[v].size();
	for (int i=0;i<sz;i++)
		if (comp[g[v][i]]==-1)
			dfs(g[v][i],com);
}

void calc(int num){
	compbest[num]=-1;
	int sz=gcomp[num].size();
	for (int i=0;i<sz;i++){
		int tmp=gcomp[num][i];
		if (compbest[num]==-1 || gr[tmp].w<gr[compbest[num]].w){
			compbest[num]=tmp;
		//	compbestcomp[num]=comp[gr[tmp].x]+comp[gr[tmp].y]-num;
		}
	}
}


bool cmp_merge(int a,int b){
	if (comp[gr[a].x]+comp[gr[a].y]!=comp[gr[b].x]+comp[gr[b].y])
		return comp[gr[a].x]+comp[gr[a].y]<comp[gr[b].x]+comp[gr[b].y];
	return gr[a].w<gr[b].w;
}

bool cmp_unique(int a,int b){
	return comp[gr[a].x]+comp[gr[a].y]==comp[gr[b].x]+comp[gr[b].y];	
}


void add(int num1,int num2){
	int sz1=gcomp[num1].size();
	int sz2=gcomp[num2].size();
	gcomp[num1].resize(sz1+sz2);
	
	for (int i=0;i<n;i++)
		if (comp[i]==num2)
			comp[i]=num1;

//	sort(gcomp[num1].begin(),gcomp[num1].end(),cmp_merge);	
//	sort(gcomp[num2].begin(),gcomp[num2].end(),cmp_merge);	
	
		
	copy(gcomp[num2].begin(),gcomp[num2].end(),gcomp[num1].begin()+sz1);
	//inplace_merge(gcomp[num1].begin(),gcomp[num1].begin()+sz1,gcomp[num1].end(),cmp_merge);
	sort(gcomp[num1].begin(),gcomp[num1].end(),cmp_merge);
	gcomp[num1].erase(unique(gcomp[num1].begin(),gcomp[num1].end(),cmp_unique),gcomp[num1].end());	

	int sz=gcomp[num1].size();
	for (int i=0;i<sz;i++)
		if (comp[gr[gcomp[num1][i]].x]==comp[gr[gcomp[num1][i]].y]){
			gcomp[num1].erase(gcomp[num1].begin()+i);
			--i;--sz;
		}
			
			
	gcomp[num2].clear();
	exist[num2]=false;
}


void iterate(){
	//cerr<<endl;	
	int bestcomp=-1;
	int bestval;
	for (int i=0;i<compn;i++)
		if (exist[i] && compbest[i]!=-1){
		//	cerr<<i<<" "<<gr[compbest[i]].w-gr[rootreb[i]].w<<endl;
			if (bestcomp==-1 || 	bestval>gr[compbest[i]].w-gr[rootreb[i]].w){
				bestcomp=i;
				bestval=gr[compbest[i]].w-gr[rootreb[i]].w;
			}		
		}
	
	if (bestcomp==-1){
		printf("-1\n");
		exit(0);
	}
	int i=bestcomp;
	assert(rootreb[i]>=0 &&  rootreb[i]<m);
	assert(gr[rootreb[i]].used);
	gr[rootreb[i]].used=false;
	assert(compbest[i]>=0 &&  compbest[i]<m);
//	assert(!gr[compbest[i]].used); 
	gr[compbest[i]].used=true;
	int comp2=comp[gr[compbest[i]].x]+comp[gr[compbest[i]].y]-i;
	add(comp2,i);
	calc(comp2);		
}

int main()
{                        
  freopen("input.txt","r",stdin);
  freopen("output.txt","w",stdout);
	int k;
	scanf("%d %d %d",&n,&m,&k);
	for (int i=0;i<m;i++){
		scanf("%d %d %d",&gr[i].x,&gr[i].y,&gr[i].w);
		--gr[i].x;--gr[i].y;
		gr[i].num=i;
		gr[i].used=false;
	}
	sort(gr,gr+m);
	
	if (n==1){
		printf("0\n");
		return 0;
	}
	
	if (k==0){
		printf("-1\n");
		return 0;
	}
	
	
	int stol=0;
	
	for (int i=0;i<m;i++)
		if (gr[i].x!=0 && gr[i].y!=0){
			if (i<k)
			{
				printf("-1\n");
				return 0;
			}
			stol=i;
			break;
		}
			
		
	init();
	
	
	for (int i=0;i<m;i++)
		if (uni(gr[i].x,gr[i].y))
			gr[i].used=true;
			
	int rkol=0;
		
	for (int i=0;i<m;i++){
		if (gr[i].used){
			rkol++;
			if (gr[i].x!=0 && gr[i].y!=0){
				g[gr[i].x].pb(gr[i].y);
				g[gr[i].y].pb(gr[i].x);
			}
		}
	}
		

	if (rkol!=n-1){
		printf("-1\n");
		return 0;
	}
	
		
	memset(comp,-1,sizeof(comp));
	for (int i=1;i<n;i++)
		if (comp[i]==-1)
		{
			dfs(i,compn);
			exist[compn]=true;
			++compn;
		}
		
	for (int i=0;i<m;i++)
		{
			int f=gr[i].x;
			int s=gr[i].y;
	//		cerr<<i<<" "<<f<<" "<<s<<" "<<gr[i].w<<endl;
			if (f==0 || s==0){
				if (s==0)
					swap(f,s);
				if (gr[i].used)
					rootreb[comp[s]]=i;	
			}
			else{
					if (comp[f]!=comp[s])
					{
						assert(!gr[i].used);
						gcomp[comp[f]].pb(i);
						gcomp[comp[s]].pb(i);
					}
			}
		}
		
	for (int i=0;i<compn;i++){
		sort(gcomp[i].begin(),gcomp[i].end(),cmp_merge);
		gcomp[i].erase(unique(gcomp[i].begin(),gcomp[i].end(),cmp_unique),gcomp[i].end());	
		calc(i);
	}
	
/*	cerr<<endl;
	for (int i=0;i<compn;i++)
	{
		copy(gcomp[i].begin(),gcomp[i].end(),ostream_iterator<int>(cerr," "));
		cerr<<endl;
	}	
	copy(rootreb,rootreb+compn,ostream_iterator<int>(cerr," "));
	cerr<<endl;
	copy(compbest,compbest+compn,ostream_iterator<int>(cerr," "));
	cerr<<endl;*/
		
	for (;stol>k;--stol)
		iterate();
		
	cout<<n-1<<endl;
	int kol=0;
	for (int i=0;i<m;i++)
		if (gr[i].used){
			printf("%d ",gr[i].num+1);
			++kol;
		}
	printf("\n");		
	//assert(kol==n-1);
  return 0;
}