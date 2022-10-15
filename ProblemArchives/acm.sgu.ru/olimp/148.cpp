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
using namespace std;

const int maxn=160;

struct node{
	int to;
	node* next;
	node* prev;
	node(){
		next=prev=0;
		to=0;
	}
};

node* g[maxn][2];
node* gmat[maxn][maxn][2];
int num[maxn][maxn];
int ans[maxn*maxn];

int mt[maxn][2];
bool used[maxn][2];
int d[maxn][2];
int n,m;
int maxd;

node* add(node* &a,int to){
	node* tmp=new node;
	tmp->next=a;
	if (a)
		a->prev=tmp;
	tmp->to=to;
	a=tmp;
	return tmp;
}

void del(node* a,int fr,int id){
	assert(a);
	if (a->prev)
		a->prev->next=a->next;
	else
		g[fr][id]=a->next;
	if (a->next)
		a->next->prev=a->prev;
}

void initmt(){
	memset(mt,-1,sizeof(mt));
}

void usemt(int iter){
	for (int i=0;i<n;i++)
		if (mt[i][0]!=-1){
			int fr=i;
			int se=mt[i][0];
			d[fr][0]--;
			d[se][1]--;
			del(gmat[fr][se][0],fr,0);
			del(gmat[se][fr][1],se,1);
			ans[num[fr][se]]=iter;
		}
}

void read(){
	scanf("%d %d",&n,&m);
	for (int i=0;i<m;i++){
		int a,b,c;
		scanf("%d %d %d",&a,&b,&c);
		--a;--b;--c;
		if (b==c)
			swap(a,b);
		gmat[a][b][0]=add(g[a][0],b);
		gmat[b][a][1]=add(g[b][1],a);
		d[a][0]++;
		d[b][1]++;
		num[a][b]=i;
	}
}

bool nechet(int v,int h,int st){
	if (used[v][h])
		return false;
	used[v][h]=true;
	if (h!=st){
		if (mt[v][h]==-1)
			return true;
		return nechet(mt[v][h],h^1,st);
	}
	for (node* iter=g[v][h];iter;iter=iter->next){
		if (nechet(iter->to,h^1,st))
			{
				mt[iter->to][h^1]=v;
				mt[v][h]=iter->to;
				return true;
			}
	}
	return false;
}

bool chet(int v,int h,int st){
	if (used[v][h])
		return false;
	used[v][h]=true;
	if (h==st){
		if (d[v][h]!=maxd){
			mt[v][h]=-1;
			return true;
		}
		for (node* iter=g[v][h];iter;iter=iter->next)
			if (chet(iter->to,h^1,st)){
				mt[iter->to][h^1]=v;
				mt[v][h]=iter->to;
				return true;
			}
		return false;
	}	
	return chet(mt[v][h],h^1,st);
}

int anskol;

bool iterate(){
	static int iter=0;
	++iter;
	initmt();
	maxd=0;
	for (int i=0;i<n;i++){
		maxd=max(maxd,d[i][1]);
		maxd=max(maxd,d[i][0]);
//		cerr<<d[i][0]<<" "<<d[i][1]<<endl;
	}
//	cerr<<maxd<<endl<<endl;;
	if (maxd==0)
		return false;
	anskol=iter;
	for (int i=0;i<n;i++)
		for (int j=0;j<2;j++)
			if (d[i][j]==maxd && mt[i][j]==-1)
				{
					memset(used,0,sizeof(used));
					bool q=nechet(i,j,j);
					if (!q){
						memset(used,0,sizeof(used));
						q=chet(i,j,j);
					}
					assert(q);
				}
	for (int i=0;i<n;i++)
		if (mt[i][0]==-1)
			{
					memset(used,0,sizeof(used));
					nechet(i,0,0);
			}
	usemt(iter);
	return true;
}



int main()
{                        
  freopen("input.txt","r",stdin);
  freopen("output.txt","w",stdout);
	read();
	for (;iterate(););
	printf("%d\n",anskol);
	for (int i=0;i<m;i++)
		printf("%d ",ans[i]);
	printf("\n");		
  return 0;
}