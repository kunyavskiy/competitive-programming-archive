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
	node* back;
	int c,f,to,num;
	node(){
		next=back=0;
		c=f=to=num=0;
	}
};

int dv;
bool used[50];
int s,t;
node* g[50];
int cur_flow;
int best_flow;
int bs,bt,bv;
int n;
const int inf=1<<30;

inline void clear_used(){
	setval(used,false);
	used[dv]=1;
}

inline void clear_flow(){
	for (int i=0;i<n;i++)
		for (node* it=g[i];it;it=it->next){
			it->c+=it->f;
			it->f=0;
		}
	cur_flow=0;
}


int dfs(int v,int mv){
	if (v==t){
		cur_flow+=mv;
		return mv;
	}
	used[v]=true;
	for (node* it=g[v];it;it=it->next){
		int to=it->to;
		int c=it->c;
		int tmp=0;
		if (!used[to] && c>0)
			 tmp=dfs(to,min(c,mv));
		if (tmp>0){
			it->f+=tmp;
			it->c-=tmp;
			it->back->f-=tmp;
			it->back->c+=tmp;
			return tmp;
		}
	}
	return 0;
}

void flow(int v){
	dv=v;
	s=t=0;
	if (s==dv)
		s++;
	for (;t<n;t++){
		if (t==s || t==v)
			continue;
		clear_flow();
		clear_used();
		for (;dfs(s,inf)>0 && cur_flow<best_flow;)
			clear_used();
		if (cur_flow<best_flow){
			best_flow=cur_flow;
			bs=s;
			bt=t;
			bv=v;
		}
		//cerr<<s<<" "<<t<<" "<<best_flow<<endl;
	}	
}

vector<int> answer;

void find_raz(){
	for (int i=0;i<n;i++)
		{
			if (i==dv)
				continue;
			if (!used[i])
				continue;
			for (node* it=g[i];it;it=it->next)
				if (!used[it->to])
					answer.pb(it->num);
		}
}

void find_ans(){
	printf("%d\n",best_flow);
	dv=bv;
	s=bs;
	t=bt;
	clear_flow();
	clear_used();
	for (;dfs(s,inf)>0;)
		clear_used();
	find_raz();
	sort(answer.begin(),answer.end());
	answer.erase(unique(answer.begin(),answer.end()),answer.end());
	printf("%d\n",answer.size());
	int sz=answer.size();
	for (int i=0;i<sz;i++)
		printf("%d ",answer[i]);	
}

void add(int a,int b,int c,int num){
	node* tmp;
	tmp=new node;
	tmp->to=b;
	tmp->c=c;
	tmp->num=num;
	tmp->next=g[a];
	g[a]=tmp;
	
	node* tmp1;
	tmp1=new node;
	tmp1->to=a;
	tmp1->c=c;
	tmp1->num=num;
	tmp1->next=g[b];
	g[b]=tmp1;
	
	tmp1->back=tmp;
	tmp->back=tmp1;
}



int main()
{
  #ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
  int m;
  scanf("%d %d",&n,&m);
  for (int i=0;i<m;i++){
  	int a,b,c;
  	scanf("%d %d %d",&a,&b,&c);
  	--a,--b;
  	add(a,b,c,i+1);
  }
  
	best_flow=inf;
	
	for (int i=0;i<n;i++)
		flow(i);
	
	find_ans();
  return 0;
}