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
	node* l;
	node* r;
	bool rev;
	int y;
	int val;
	int kol;
	node(){
		l=r=0;
		rev=false;
		y=rand();
		val=0;
		kol=1;
	}
	node(int v){
		l=r=0;
		rev=false;
		y=rand();
		val=v;
		kol=1;
	}
};

node* root;

void update(node* v){
	if (!v)
		return;
	v->kol=1;
	if (v->l)
		v->kol += v->l->kol;
	if (v->r)
		v->kol += v->r->kol;
	return;		
}

void push(node* v){
	if (!v)
		return;
	if (!v->rev)
		return;
	swap(v->l,v->r);
	if (v->l)
		v->l->rev^=1;
	if (v->r)
		v->r->rev^=1;
	v->rev=0;
}

node* merge(node* l,node* r){
	if (!l)
		return r;
	if (!r)
		return l;
	push(l);
	push(r);
	if (l->y > r->y)
		{
			l->r=merge(l->r,r);
			update(l);
			return l;
		}
	r->l = merge(l,r->l);
	update(r);
	return r;
}

void split(node* v,int kol,node* &l,node* &r){
	//cerr<<v->val<<" "<<v->kol<<endl;
	if (kol==0){
		l=0;
		r=v;
		return;
	}
	if (!v)
	{
		l=r=0;
		return;
	}
	push(v);
	if (v->l){
		if (v->l->kol >= kol)
			{
				r=v;
				split(v->l,kol,l,v->l);
				update(r);
				return;
			}
		kol-= v->l->kol;
	}
	
	l=v;
	--kol;
	
	split(v->r,kol,v->r,r);
	update(l);
}

void rev(int L,int R){
	node *l, *m, *r;
	split(root,R,l,r);
	split(l,L-1,l,m);
	assert(m);
	m->rev^=1;
	l=merge(l,m);
	root=merge(l,r);
}

void print(node* v){
	if (!v)
		return;
	push(v);
	print(v->l);
	printf("%d ",v->val);
	print(v->r);
}

int main()
{
  #ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
  
  int n,m;
  scanf("%d %d",&n,&m);
  root=0;
  for (int i=1;i<=n;i++){
  	node* tmp;
  	tmp=new node(i);
  	root=merge(root,tmp);
  }
  
  for (int i=0;i<m;i++){
  	int l,r;
  	scanf("%d %d",&l,&r);
  	rev(l,r);
  }
  
  print(root);
  return 0;
}