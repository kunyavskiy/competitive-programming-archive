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
	node *next,*back;
	int c,w,f;
	int to;
};

node* g[1100];
const int inf=1<<28;

int s,t;
int a[1100];
int n;
int pot[1100];

void add(int v,int to,int c,int w){
	node *tmp1,*tmp2;
	tmp1=new node();
	tmp2=new node();
	(tmp1->back=tmp2)->back=tmp1;
	tmp1->w=w;
	tmp2->w=-w;
	tmp1->to=to;
	tmp2->to=v;
	tmp1->f=tmp2->f=tmp2->c=0;
	tmp1->c=c;
	tmp1->next=g[v];
	g[v]=tmp1;
	tmp2->next=g[to];
	g[to]=tmp2;
}

void gen(){
	s=n;
	t=n+1;
	for (int i=0;i<n;i++){
		add(s,i,a[i],0);
		add(i,t,1,0);
		add(i,(i+1)%n,inf,1);
		add(i,(i+n-1)%n,inf,1);
	}
	n+=2;
}

int d[1100];
node* p[1100];

void use(int t){
	while (t!=s){
		p[t]->f++;
		p[t]->c--;
		p[t]->back->f--;
		p[t]->back->c++;
		t=p[t]->back->to;
	}
}

bool dijkstra(){
	for (int i=0;i<n;i++){
		d[i]=inf;
		p[i]=0;
	}
	d[s]=0;
	set<pair<int,int> > st;
	st.insert(mp(0,s));
	for (;!st.empty();){
		int v=st.begin()->second;
		st.erase(st.begin());
		for (node* it=g[v];it;it=it->next){
			if (!it->c)
				continue;
			int w=it->w+(pot[v]-pot[it->to]);
			assert(w>=0);
			if (d[it->to]<=d[v]+w)
				continue;
			st.erase(mp(d[it->to],it->to));
			d[it->to]=d[v]+w;
			p[it->to]=it;
			st.insert(mp(d[it->to],it->to));
		}
	}
	if (p[t]==0)
		return false;
	for (int i=0;i<n;i++)
		pot[i]+=d[i];
	use(t);
	return true;
}


int main()
{                        
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
	scanf("%d",&n);
	for (int i=0;i<n;i++)
		scanf("%d",&a[i]);
	gen();
	for (;dijkstra(););
	int ans=0;
	for (int i=0;i<n;i++)
		for (node* it=g[i];it;it=it->next)
			if (it->f > 0)
				ans+=it->f * it->w;
	printf("%d\n",ans);
    return 0;
}