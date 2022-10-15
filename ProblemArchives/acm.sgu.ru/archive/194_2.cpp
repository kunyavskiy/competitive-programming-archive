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
	bool unused;
	bool full;
	node(){
		next=back=0;
		to=num=c=f=from=0;
		unused=full=0;
	}
	node(int From,int To,int C,int Num){
		next=back=0;
		to=To;
		c=C;
		from=From;
		num=Num;
		f=0;
		unused=full=false;
	}
};

node* g[210];
node* ptr[210];
int n,m;
int s,t;
int d[210];
const int inf=1<<30;
int flow[210*210+10];
bool used[210];

int dfs(int v,int minv,int rmin){
//	cerr<<v<<" "<<minv<<" "<<rmin<<endl;
	if (v==t)
		return minv;
	used[v]=true;
	for (node* it=g[v];it;it=it->next){
		if (it->c<rmin)
			continue;
		if (it->unused)
			continue;
		if (used[it->to])
			continue;
		int tmp=dfs(it->to,min(minv,it->c),rmin);
		if (tmp>0){
	//		cerr<<"BACK "<<it->from<<" "<<it->to<<" "<<tmp<<endl;
			it->f+=tmp;
			it->c-=tmp;
			it->back->f-=tmp;
			it->back->c+=tmp;
			return tmp;
		}
	}
	return 0;
}



void add(int a,int b,int L,int R,int num){
	node* l=new node(a,b,L,num);
	node* lb=new node(b,a,0,-1);
	node* r=new node(a,b,R-L,num);
	node* rb=new node(b,a,0,-1);
	l->back=lb;
	lb->back=l;
	r->back=rb;
	rb->back=r;
	l->full=true;
	r->next=l;
	rb->next=lb;
	l->next=g[a];
	lb->next=g[b];
	g[a]=r;
	g[b]=rb;
}

void add(int a,int b,int R){
	node* r=new node(a,b,R,-1);
	node* rb=new node(b,a,0,-1);
	r->back=rb;
	rb->back=r;
	r->next=g[a];
	rb->next=g[b];
	g[a]=r;
	g[b]=rb;
}

void see(){
	cerr<<s<<" "<<t<<endl;
	for (int i=0;i<n;i++)
		for (node* it=g[i];it;it=it->next)
			fprintf(stderr,"(%d %d %d)%c",it->to,it->c,it->f," \n"[!(it->next)]);
}


int main()
{
  #ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
  scanf("%d %d",&n,&m);
 // assert(n!=1);
  for (int i=0;i<m;i++){
  	int a,b,l,r;
  	scanf("%d %d %d %d",&a,&b,&l,&r);
  	--a,--b;
  //	cerr<<a<<" "<<b<<" "<<l<<" "<<r<<endl;
  	add(a,b,l,r,i);
    //see();
  }
  
    
  n+=2;
  s=n-2;
  t=n-1;
  
  
  for (int i=0;i<n-2;i++){
  	for (node* it=g[i];it;it=it->next)
  		if (it->full){
  			it->unused=it->back->unused=true;
				add(s,it->to,it->c);
				add(it->from,t,it->c);
  		}
  }
  
	for (int r=1<<30;r;r/=2)
	{
		setval(used,false);
		for (;dfs(s,inf,r)>0;)
		{
			setval(used,false);
		//	see();
		}
	}

//	see();	 
    
  for (node* it=g[s];it;it=it->next){
  	if (it->c!=0)
  	{
  		printf("NO\n");
  		return 0;
  	}  	
  }
  
  n-=2;
  
  for (int i=0;i<n;i++){
  	for (node* it=g[i];it;it=it->next)
  		if (it->full){
  			it->unused=it->back->unused=false;
				it->f=it->c;
				it->back->f=-it->f;
  		}
  }
  
  for (int i=0;i<n;i++)
  	for (node* it=g[i];it;it=it->next)
  		if (it->num!=-1)
  			flow[it->num]+=it->f;
  			
  printf("YES\n");
  for (int i=0;i<m;i++)
  	printf("%d\n",flow[i]);
  
  return 0;
}