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

struct node{
	node* next;
	int from;
	int to;
	int num;
	int c;
	int f;
	node* back;
	node(){
		next=back=0;
		to=num=c=f=from=0;
	}
	node(int From,int To,int C,int Num){
		next=back=0;
		to=To;
		c=C;
		from=From;
		num=Num;
		f=0;                
	}
};

node* g[210];
node* ptr[210];
int n,m;
int s,t;
int d[210];
const int inf=1<<30;
int flow[210*210+10];
int inl[210];
int outl[210];  


int dfs(int v,int have){
	if (v==t)
		return have;
	int prot=0;
	for (;ptr[v];){
		if (ptr[v]->c==0 || d[ptr[v]->to]!=d[v]+1){
			ptr[v]=ptr[v]->next;
			continue;
		}
		int tmp=dfs(ptr[v]->to,min(have-prot,ptr[v]->c));
		prot+=tmp;
		ptr[v]->f+=tmp;
		ptr[v]->c-=tmp;
		ptr[v]->back->f-=tmp;
		ptr[v]->back->c+=tmp;
		if (have==prot)
			break;
		ptr[v]=ptr[v]->next;
	}
	return prot;
}

int bfs(){
	static int dest=-1;
	for (int i=0;i<n;i++)
		d[i]=inf;
	d[s]=0;
	queue<int> q;
	q.push(s);
	for (;!q.empty();){
		int fr=q.front();
		q.pop();
		for (node* it=g[fr];it;it=it->next){
			if (it->c==0)
				continue;
			if (d[it->to]<d[fr]+1)
				continue;
			d[it->to]=d[fr]+1;
			q.push(it->to);
		}
	}
	
	if (d[t]==inf)
		return 0;
		
	dest=d[t];
	
	for (int i=0;i<n;i++)
		ptr[i]=g[i];

	return dfs(s,inf);	
}

void add(int a,int b,int c,int num){
	node* tmp=new node(a,b,c,num);
	node* tmpb=new node(b,a,0,-1);
	tmp->next=g[a];
	g[a]=tmp;
	tmp->back=tmpb;
	tmpb->next=g[b];
	g[b]=tmpb;
	tmpb->back=tmp;	
}


int main()
{
  #ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
  scanf("%d %d",&n,&m);
  for (int i=0;i<m;i++){
  	int a,b,l,r;
  	scanf("%d %d %d %d",&a,&b,&l,&r);
  	--a,--b;
  	outl[a]+=l;
  	inl[b]+=l;
  	flow[i]=l;
  	add(a,b,r-l,i);
  }
  
    
  n+=2;
  s=n-2;
  t=n-1;
  
  
  for (int i=0;i<n-2;i++){
  	add(s,i,inl[i],-1);
  	add(i,t,outl[i],-1);
  }
  
	for (;bfs()>0;);

  for (node* it=g[s];it;it=it->next){
  	if (it->c!=0)
  	{
  		printf("NO\n");
  		return 0;
  	}  	
  }
  
  n-=2;
 
  for (int i=0;i<n;i++)
  	for (node* it=g[i];it;it=it->next)
  		if (it->num!=-1)
  			flow[it->num]+=it->f;
  			
  printf("YES\n");
  for (int i=0;i<m;i++)
  	printf("%d\n",flow[i]);
  
  return 0;
}